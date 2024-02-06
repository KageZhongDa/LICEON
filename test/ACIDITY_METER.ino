// Define the pin for the acidity sensor
#define aciditySensor A3

// Variables for acidity sensor calibration and measurements
float acidtyCalibrationValue = 23.1;
unsigned long int acidityAverageValue;
int buffer_arr[10], acidityTemperatureValue;

float acidityActualValue;

void setup() {
  // Start serial communication at 9600 baud
  Serial.begin(9600);
}

void loop() {
  // Read acidity sensor values into the buffer array
  for (int i = 0; i < 10; i++) {
    buffer_arr[i] = analogRead(aciditySensor);
    delay(30);
  }

  // Sort the buffer array in ascending order
  for (int i = 0; i < 9; i++) {
    for (int j = i + 1; j < 10; j++) {
      if (buffer_arr[i] > buffer_arr[j]) {
        acidityTemperatureValue = buffer_arr[i];
        buffer_arr[i] = buffer_arr[j];
        buffer_arr[j] = acidityTemperatureValue;
      }
    }
  }

  // Calculate the average value of the sensor readings (excluding extremes)
  acidityAverageValue = 0;
  for (int i = 2; i < 8; i++)
    acidityAverageValue += buffer_arr[i];

  // Convert the sensor readings to pH value using calibration
  float voltage = (float)acidityAverageValue * 5.0 / 1024 / 6;
  acidityActualValue = -5.70 * voltage + acidtyCalibrationValue;

  // Print the pH value to the serial monitor
  Serial.println("pH Val: ");
  Serial.print(acidityActualValue);

  // Delay for 100 milliseconds
  delay(100);
}
