
void setup() {
Serial.begin(115200); //Baud rate: 115200
}

void loop() {
int sensorValue = analogRead(35);// read the input on analog pin 0:
float voltage = sensorValue * (3.3 / 4095); // Convert the analog reading (which goes from 0 – 1023) to a voltage (0 – 5V):
Serial.println(voltage); // print out the value you read:
delay(500);
}