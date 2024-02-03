#include <OneWire.h>
#include <DallasTemperature.h>


#define temperatureSensor = A0; // try.. works on digital pins only
#define turbiditySensor = A1;
#define aciditySensor = A3;


// ====================================
//               TEMPERATURE
// ====================================


// Setup a oneWire instance to communicate with any OneWire devices
OneWire temperatureWire(temperatureSensor);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature temperature(&temperatureWire);



// ====================================
//               ACIDITY
// ====================================

float acidityActualValue;
float acidtyCalibrationValue = 23.1;
unsigned long int acidityAverageValue;
int buffer_arr[10], acidityTemperatureValue;



// ====================================
//               SETUP
// ====================================

void setup() {
  Serial.begin(115200);

   temperature.begin();
   pinMode(turbiditySensor, INPUT);
   pinMode(aciditySensor, INPUT);

}


// ====================================
//               LOOP
// ====================================


void loop() {

   // ====================================
   //               TEMPERATURE
   // ====================================

   // Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
  temperature.requestTemperatures(); 
  
  Serial.print("Celsius temperature: ");
  // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  Serial.print(sensors.getTempCByIndex(0)); 
  Serial.print(" - Fahrenheit temperature: ");
  Serial.println(sensors.getTempFByIndex(0));


   // ====================================
   //               ACIDITY
   // ====================================

   for (int i = 0; i < 10; i++) {
      buffer_arr[i] = analogRead(aciditySensor);
      delay(30);
   }

   for (int i = 0; i < 9; i++) {
      for (int j = i + 1; j < 10; j++) {
         if (buffer_arr[i] > buffer_arr[j]) {
         acidityTemperatureValue = buffer_arr[i];
         buffer_arr[i] = buffer_arr[j];
         buffer_arr[j] = acidityTemperatureValue;
         }
      }
   }

   acidityAverageValue = 0;
   for (int i = 2; i < 8; i++)
      acidityAverageValue += buffer_arr[i];

   float voltage = (float)acidityAverageValue * 5.0 / 1024 / 6;
   acidityActualValue = -5.70 * voltage + acidtyCalibrationValue;

   Serial.println("pH Val: ");
   Serial.print(acidityActualValue);
   



   // ====================================
   //               TURBIDITY
   // ====================================

   // read the input on analog pin 0:
   int turbidityValue = analogRead(turbiditySensor);
   // print out the value you read:
   Serial.println(turbidityValue);

   delay(100);
}

