// network library
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

// temperature sensor library
#include <OneWire.h>
#include <DallasTemperature.h>

// Define Hotspot credentials
const char *ssid = "LICEON_ESP32";
const char *password = "password";


// Define pin numbers for sensors
#define TEMPERATURE_SENSOR 0   // ADC1
#define TURBIDITY_SENSOR 35    // ADC1
#define ACIDITY_SENSOR 34      // ADC2


// ====================================
//             WiFi Module
// ====================================

// Create an instance of the server
AsyncWebServer server(80);

// ====================================
//             TemperatureSensor
// ====================================

class TemperatureSensor {
private:
  OneWire oneWire;
  DallasTemperature temperatureSensor;

public:
  // Constructor initializes the OneWire and DallasTemperature objects
  TemperatureSensor(int pin) : oneWire(pin), temperatureSensor(&oneWire) {
    temperatureSensor.begin();
  }

  // Method to get temperature in Celsius
  float getTemperatureCelsius() {
    temperatureSensor.requestTemperatures();
    return temperatureSensor.getTempCByIndex(0);
  }

  // Method to get temperature in Fahrenheit
  float getTemperatureFahrenheit() {
    temperatureSensor.requestTemperatures();
    return temperatureSensor.getTempFByIndex(0);
  }
};

// Create an instance of TemperatureSensor
TemperatureSensor tempSensor(TEMPERATURE_SENSOR);

// ====================================
//              AciditySensor
// ====================================

class AciditySensor {
private:
  float actualValue;
  unsigned long int averageValue;
  int buffer[10], temperatureValue;

    // Function to map voltage to pH using linear interpolation
  float mapVoltageToPH(float voltage) {
    // Given data points
    float voltagePoints[] = {2.09, 2.25, 3.2};
    float phPoints[] = {9, 7, 2};

    // Ensure the voltage is within the range of the data points
    if (voltage <= voltagePoints[0]) {
      return phPoints[0];
    }
    if (voltage >= voltagePoints[2]) {
      return phPoints[2];
    }

    // Perform linear interpolation
    float ph = phPoints[1] + (voltage - voltagePoints[1]) * (phPoints[2] - phPoints[1]) / (voltagePoints[2] - voltagePoints[1]);

    return ph;
  }

public:
  // Constructor
  AciditySensor() {}

  // Method to perform acidity measurement
  float measure() {
    for (int i = 0; i < 10; i++) {
      buffer[i] = analogRead(ACIDITY_SENSOR);
      delay(30);
    }

    // Sort buffer array in ascending order
    for (int i = 0; i < 9; i++) {
      for (int j = i + 1; j < 10; j++) {
        if (buffer[i] > buffer[j]) {
          temperatureValue = buffer[i];
          buffer[i] = buffer[j];
          buffer[j] = temperatureValue;
        }
      }
    }

    averageValue = 0;
    for (int i = 2; i < 8; i++)
      averageValue += buffer[i];

    // float voltage = (float)averageValue * 5.0 / 1024 / 6;
    float voltage = (float)averageValue * 3.3 / 4095 / 6;
    
    // actualValue = -5.5 * voltage + calibrationValue;
    actualValue = mapVoltageToPH(voltage);

    return actualValue + 0.4;
  }
};

// Create an instance of AciditySensor
AciditySensor aciditySensor;

// ====================================
//             TurbiditySensor
// ====================================

class TurbiditySensor {
private:
  int sensorPin;

public:
  // Constructor
  TurbiditySensor(int pin) : sensorPin(pin) {
    pinMode(sensorPin, INPUT);
  }

  // Method to perform turbidity measurement
  int measure() {
    // Read the input on the analog pin
    return 4095 - analogRead(sensorPin);
  }
};

// Create an instance of TurbiditySensor
TurbiditySensor turbiditySensor(TURBIDITY_SENSOR);
 
// ====================================
//               SETUP
// ====================================

void setup() {
  // Start serial communication
  Serial.begin(9600);

  // ====================================
  //          WiFi CONNECTION
  // ====================================
  // Set up the Access Point
  WiFi.softAP(ssid, password);

  // Print the Ip Address to the serial on startup
  Serial.println("Access Point Started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  // ====================================
  //           API DATA ROUTE
  // ====================================
  server.on("/api/data", HTTP_GET, [](AsyncWebServerRequest *request) {

  float acdVal    = aciditySensor.measure();
  int trbVal      = turbiditySensor.measure(); 
  float tmpCelVal = tempSensor.getTemperatureCelsius();
  float tmpFarVal = tempSensor.getTemperatureFahrenheit();

  // Create a JSON object
  DynamicJsonDocument jsonDoc(1024);
  
  // Add data to the JSON object
  jsonDoc["SERVER"] = "LICEON";
  jsonDoc["ACDVAL"] = acdVal;
  jsonDoc["TRBVAL"] = trbVal;
  jsonDoc["TMPCELVAL"] = tmpCelVal;
  jsonDoc["TMPFARVAL"] = tmpFarVal;

  // Serialize the JSON object to a string
  String jsonString;
  serializeJson(jsonDoc, jsonString);

  // Send the JSON response
  request->send(200, "application/json", jsonString);
});

  // Start server
  server.begin();
}

// ====================================
//               LOOP
// ====================================

void loop() {}
