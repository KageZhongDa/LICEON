// Define variable to store pH value
int pH_Value;

// Define variable to store voltage
float Voltage;

void setup() {
  // Start serial communication at 9600 baud
  Serial.begin(9600);

  // Set pH_Value pin as INPUT
  pinMode(pH_Value, INPUT);
}

void loop() {
  // Read analog value from pH sensor connected to pin A0
  pH_Value = analogRead(A0);

  // Convert analog value to voltage (assuming 5V reference)
  Voltage = pH_Value * (5.0 / 1023.0);

  // Print the voltage to the serial monitor
  Serial.println(Voltage);

  // Delay for 500 milliseconds
  delay(500);
}
