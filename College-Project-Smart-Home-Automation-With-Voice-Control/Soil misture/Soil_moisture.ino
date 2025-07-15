#define soilPin A0     // Soil moisture sensor analog pin
#define pumpPin D1     // Pump connected via relay module

int threshold = 700;   // Adjust this value based on testing

void setup() {
  Serial.begin(9600);
  pinMode(pumpPin, OUTPUT);
  digitalWrite(pumpPin, HIGH); // Start with pump off
}

void loop() {
  int moisture = analogRead(soilPin);
  Serial.print("Soil Moisture: ");
  Serial.println(moisture);

  if (moisture > threshold) {
    // Soil is dry, turn on pump
    digitalWrite(pumpPin, LOW);
    Serial.println("Pump ON");
  } else {
    // Soil is wet, turn off pump
    digitalWrite(pumpPin, HIGH);
    Serial.println("Pump OFF");
  }

  delay(1000); // 1 second delay for stability
}
