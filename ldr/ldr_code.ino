int ldrPin = A0;    // LDR connected to analog pin A0
int ledPin = 6;     // LED connected to pin 6 (through 220Ω resistor)
int ldrValue = 0;   // variable to store LDR value

// Adjust this threshold based on your LDR readings
int ldrThreshold = 500;  

void setup() {
  Serial.begin(9600); // start serial communication
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // LED OFF initially
}

void loop() {
  ldrValue = analogRead(ldrPin); // read value from LDR

  Serial.print("LDR Value: ");
  Serial.println(ldrValue);      // print value to Serial Monitor

  // Control LED

// int sum = 0;
// for (int i = 0; i < 10; i++) {
//   sum += analogRead(ldrPin);
//   delay(10);
// }
// ldrValue = sum / 10;

  if (ldrValue < ldrThreshold) {
    digitalWrite(ledPin, HIGH);  // Dark -> LED ON
  } else {
    digitalWrite(ledPin, LOW);   // Bright -> LED OFF
  }

  delay(500); // wait half second before next read
}
