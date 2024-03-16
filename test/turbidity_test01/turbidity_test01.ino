#include <Arduino.h>
#include <DallasTemperature.h>

#define TEMPERATURE_SENSOR 0
// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(TEMPERATURE_SENSOR);	

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

int sensorPin = 35; //code taken online
float volt;
float ntu;

float temp_data = 25.0;

float TU_value = 0.0;
float TU_calibration = 0.0;

void setup() {
  Serial.begin(115200);
}

void loop() {
  volt = 0;


  // Send the command to get temperatures
  sensors.requestTemperatures(); 
  double temp = sensors.getTempCByIndex(0);

  //Calculate Average Voltage Values
  for(int i=0; i<800; i++) {
    volt += ((float)analogRead(sensorPin)/4095)*3.3;
  }
  volt = volt/725;
  
  
  /*if(volt < 0.9) {
    ntu = 1000;
  } else {
    double number = volt;
    double squared = pow(number,2);
    ntu = ((-1120.4*squared+5742.3*volt-4353.8)/3); 
    Serial.println(ntu);
  }
*/

 // int sensorValue = analogRead(sensorPin);// read the input on analog pin 0:
  //float ntu = sensorValue * (3.3 / 4095.0);
  float TU_calibration = -0.0192 * (temp- 25);
  float standardVolt = volt - TU_calibration;
  double number = standardVolt;
  double squared = pow(number,2);
  float ntu = ((-1120.4*squared+5742.3*standardVolt-4353.8)/3); 
  float ntuFinal = 1000 - ntu;

  if (ntuFinal <= 0) { ntuFinal = 0; }
  if (ntuFinal >= 1000) { ntuFinal = 1000; }

  Serial.print("Voltage: ");
  Serial.print(volt);
  Serial.print(" Temperature: ");
  Serial.print(temp);
  Serial.print((char)176);//shows degrees character
  Serial.print("C  |  ");
  Serial.print(" V, NTU: ");
  Serial.print(ntuFinal);
  Serial.println(" NTU");
  delay(1000);

/*
   pinMode(cdzhuo, LOW);
    pinMode(cdph, HIGH);
    delay(1000);
    int sensorValue = analogRead(A0);// read the input on analog pin 0:
    float TU
               (5.0 / 1024.0); // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
    TU_calibration = -0.0192 * (temp_data - 25) + TU;
    TU_value = -865.68 * TU_calibration + K_Value;

    if (TU_value <= 0) { TU_value = 0; }
    if (TU_value >= 3000) { TU_value = 3000; }
  */
}

float round_to_dp(float in_value, int decimal_place) {
  float multiplier = powf(10.0f, decimal_place);
  in_value = roundf(in_value * multiplier) / multiplier;
  return in_value;
}
