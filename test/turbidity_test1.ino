int sensorPin = 35; //code taken online
float volt;
float ntu;

void setup() {
  Serial.begin(115200);
}

void loop() {
  volt = 0;
  for(int i=0; i<800; i++) {
    volt += ((float)analogRead(sensorPin)/4095)*3.3;
  }
  volt = volt/800;
  volt = round_to_dp(volt, 2);
  if(volt < 1.65) {
    ntu = 3000;
  } else {
    ntu = -1120.4*square(volt)+5742.3*volt-4353.8; 
  }
  Serial.print("Voltage: ");
  Serial.print(volt);
  Serial.print(" V, NTU: ");
  Serial.print(ntu);
  Serial.println(" NTU");
  delay(10);
}

float round_to_dp(float in_value, int decimal_place) {
  float multiplier = powf(10.0f, decimal_place);
  in_value = roundf(in_value * multiplier) / multiplier;
  return in_value;
}