#include <OneWire.h>
#include <DallasTemperature.h>

#define TEMPERATURE_SENSOR 0


 // ====================================
//               TEMPERATURE
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

void setup() {
Serial.begin(115200); //Baud rate: 115200
}

void loop() {
 

int sensorValue = analogRead(35);// read the input on analog pin 0:
float voltage = (4095 - sensorValue) * 3.3 / 4095.0; // Convert the analog reading (which goes from 0 – 1023) to a voltage (0 – 5V):
float probot = (865.68 * voltage) + 64.32;
float ntu = map(sensorValue, 4095, 0, 0, 100); // Map the sensor value to the NTU range
int sensorval = 4095 - sensorValue;

float tempC = tempSensor.getTemperatureCelsius();

Serial.println(ntu); // print out the value you read:
Serial.println(tempC);
delay(1000);
}