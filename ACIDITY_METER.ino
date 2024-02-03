#define aciditySensor = A3;


float acidtyCalibrationValue = 23.1;
unsigned long int acidityAverageValue;
int buffer_arr[10], acidityTemperatureValue;

float acidityActualValue;

void setup() {
  Serial.begin(9600);
}

void loop() {
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
  delay(100);
}
