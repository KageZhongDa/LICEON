#include <OneWire.h>
#include <DallasTemperature.h>

// Define pin numbers for sensors
#define TEMPERATURE_SENSOR 0
#define TURBIDITY_SENSOR 35
#define ACIDITY_SENSOR 34

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
  float calibrationValue = 20;
  unsigned long int averageValue;
  int buffer[10], temperatureValue;

public:
  // Constructor
  AciditySensor() {}

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

    Serial.println(voltage);
    return actualValue;
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
    return analogRead(sensorPin);
  }
};

// Create an instance of TurbiditySensor
TurbiditySensor turbiditySensor(TURBIDITY_SENSOR);

// ====================================
//               SETUP
// ====================================

void setup() {
  Serial.begin(115200);
}

// ====================================
//               LOOP
// ====================================

void loop() {
  
  float acidVal = aciditySensor.measure();
  float tempCelVal = tempSensor.getTemperatureCelsius();
  float tempFarVal = tempSensor.getTemperatureFahrenheit();

  // 4095 clear
  // 0 dense cloud
  int turbVal = turbiditySensor.measure();

  // Acidity measurement
  Serial.print("Acid Value: ");
  Serial.print(acidVal);

  // Turbidity measurement
  Serial.print(" | Turbidity Value: ");
  Serial.print(turbVal);
  
  // Temperature measurement
  Serial.print(" | Celsius temperature: ");
  Serial.print(tempCelVal);
  Serial.print(" | Fahrenheit temperature: ");
  Serial.print(tempFarVal);
  Serial.println("\n==================================================================\n");
  delay(1000);
}
