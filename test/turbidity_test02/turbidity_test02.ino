#include <OneWire.h>
#include <DallasTemperature.h>

#define TEMPERATURE_SENSOR 0

int sensorPin = 35; //code taken online
float volt;
float ntu;


 // ====================================
//               TEMPERATURE
// ====================================
//class TemperatureSensor {
//private:
  //OneWire oneWire;
  //DallasTemperature temperatureSensor;

//public:
  // Constructor initializes the OneWire and DallasTemperature objects
  //TemperatureSensor(int pin) : oneWire(pin), temperatureSensor(&oneWire) {
    //temperatureSensor.begin();
  //}

  // Method to get temperature in Celsius
  //float getTemperatureCelsius() {
    //temperatureSensor.requestTemperatures();
    //return temperatureSensor.getTempCByIndex(0);
  //}

  // Method to get temperature in Fahrenheit
  //float getTemperatureFahrenheit() {
    //temperatureSensor.requestTemperatures();
    //return temperatureSensor.getTempFByIndex(0);
  //}
//};

// Create an instance of TemperatureSensor
//TemperatureSensor tempSensor(TEMPERATURE_SENSOR);

void setup() {
Serial.begin(115200); //Baud rate: 115200
//pinMode(34,INPUT);
}

void loop() {

  volt = 0;

  //Calculate Average Voltage Values
  for(int i=0; i<800; i++) {
    volt += ((float)analogRead(sensorPin)/4095)*3.3;
  }
  volt = volt/725;
  if(volt < 0.92) {
    ntu = 1000;
  } else {
    double number = volt;
    double squared = pow(number,2);
    ntu = 1000 - ((-1120.4*squared+5742.3*volt-4353.8)/3); 
  }
  delay(1000);
 

int digital = digitalRead(34);
int sensorValue = analogRead(35);// read the input on analog pin 0:
float voltage = sensorValue * 3.3 / 4095.0; // Convert the analog reading (which goes from 0 – 1023) to a voltage (0 – 5V):
float probot = (865.68 * voltage) + 64.32;
float ntumap = map(sensorValue, 2045, 0, 0, 1000); // Map the sensor value to the NTU range
int sensorval = 4095 - sensorValue;

//float tempC = tempSensor.getTemperatureCelsius();

//Serial.println(sensorValue); // print out the value you read:
Serial.println(ntu);
//Serial.print(tempC);
}