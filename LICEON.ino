/// Include required libraries for WiFi, AsyncWebServer, ArduinoJson, and sensor components
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Define WiFi credentials
const char *ssid = "KASERVPOT"; // Replace with your WiFi network name
const char *pass = "password"; // Replace with your WiFi password

float trbvolt;
float ntuFinal;

// Define pin numbers for sensors
#define TEMPERATURE_SENSOR 0 // Pin connected to the temperature sensor (ADC1)
#define TURBIDITY_SENSOR 35 // Pin connected to the turbidity sensor (ADC1)
#define ACIDITY_SENSOR 34 // Pin connected to the acidity sensor (ADC2)

// Create an instance of the server
AsyncWebServer server(80);

// Define the TemperatureSensor class
class TemperatureSensor {
private:
  OneWire oneWire;
  DallasTemperature temperatureSensor;

public:
  // Constructor initializes OneWire and DallasTemperature objects
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

// Define the AciditySensor class
class AciditySensor {
private:
  float actualValue;
  unsigned long int averageValue;
  int buffer[10], temperatureValue;

  // Function to map voltage to pH using linear interpolation
  float mapVoltageToPH(float voltage) {
    // Given data points
    float voltagePoints[] = {2.10, 2.47, 3.10};
    float phPoints[] = {9.18, 6.86, 4.01};

    // Ensure voltage is within range of data points
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
      buffer[i] = analogRead(ACIDITY_SENSOR); // Read analog value from acidity sensor
      delay(30); // Delay for stability
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

    // Convert averageValue to voltage
    float voltage = (float)averageValue * 3.3 / 4095 / 6; // 3.3V reference, 12-bit ADC resolution

    // Map voltage to pH value
    actualValue = mapVoltageToPH(voltage);

    return actualValue; // Adjust for calibration or offset
  }
};

// Create an instance of AciditySensor
AciditySensor aciditySensor;

// Define the TurbiditySensor class
class TurbiditySensor {
private:
  int sensorPin;

public:
  // Constructor
  TurbiditySensor(int pin) : sensorPin(pin) {
    pinMode(sensorPin, INPUT); // Set pin mode to INPUT
  }

  // Method to perform turbidity measurement
  int measure() {
    trbvolt = 0;
    for(int i=0; i<800; i++) {
    trbvolt += ((float)analogRead(TURBIDITY_SENSOR)/4095)*3.3;
    }
    trbvolt = trbvolt/725;
    float tempC = tempSensor.getTemperatureCelsius();
    float TU_calibration = -0.0192 * (tempC - 25);
    float standardVolt = trbvolt - TU_calibration;
    double number = standardVolt;
    double squared = pow(number,2);
    float ntu = ((-1120.4*squared+5742.3*standardVolt-4353.8)/3); 
    float ntuFinal = 1000 - ntu;

  if (ntuFinal <= 0) { ntuFinal = 0; };
  if (ntuFinal >= 1000) { ntuFinal = 1000; };
    // Read analog value from turbidity sensor
  return ntuFinal;
  }
};

// Create an instance of TurbiditySensor
TurbiditySensor turbiditySensor(TURBIDITY_SENSOR);
void setup(){
  wifi();
}
// Setup function
void wifi() {
  // Start serial communication
  Serial.begin(115200);

  // Connect to WiFi network
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000); // Wait for connection
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP()); // Print local IP address

  // Define route for API data
  server.on("/api/data", HTTP_GET, [](AsyncWebServerRequest *request) {
    // Measure sensor values
    float acdVal = aciditySensor.measure();
    int trbVal = turbiditySensor.measure();
    float tmpCelVal = tempSensor.getTemperatureCelsius();
    float tmpFarVal = tempSensor.getTemperatureFahrenheit();

    // Create JSON object
    DynamicJsonDocument jsonDoc(1024);

    // Add data to JSON object
    jsonDoc["SERVER"] = "LICEON";
    jsonDoc["ACDVAL"] = acdVal;
    jsonDoc["TRBVAL"] = trbVal;
    jsonDoc["TMPCELVAL"] = tmpCelVal;
    jsonDoc["TMPFARVAL"] = tmpFarVal;

    // Serialize JSON object to string
    String jsonString;
    serializeJson(jsonDoc, jsonString);

    // Send JSON response
    request->send(200, "application/json", jsonString);
  });

  // Start server
  server.begin();
}
// Loop function
void loop() {}
//void loop2(){
  //Serial.println(aciditySensor.measure());
  //Serial.println(turbiditySensor.measure());
  //Serial.println(tempSensor.getTemperatureCelsius());
//}