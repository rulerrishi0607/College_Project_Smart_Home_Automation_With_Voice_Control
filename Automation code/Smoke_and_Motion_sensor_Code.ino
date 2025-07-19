#define BLYNK_TEMPLATE_ID "TMPL2rnc19JGB"
#define BLYNK_TEMPLATE_NAME "Smoke and motion sensor"
#define BLYNK_AUTH_TOKEN "ZFyJYyJ4XSjIQpf61yXoCmU4WU-Tfzqy"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Your WiFi credentials
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "MdNabilAhmed";  // Type your WiFi name
char pass[] = "Nabil12345";    // Type your WiFi password

// Define the pins for the smoke sensor, relay, buzzer, motion sensor, and LED
int smokeA0 = A0;
int relayPin = D1;   // Pin connected to the relay
int buzzerPin = D2;  // Pin connected to the buzzer
int motionSensorPin = D3; // Pin connected to the motion sensor
int ledPin = D6; // Pin connected to the LED
int sensorThres = 130;

BlynkTimer timer;

void sendSmokeSensorData() {
  int data = analogRead(smokeA0);
  Blynk.virtualWrite(V0, data);

  // Print threshold and current sensor reading
  Serial.print("Threshold: ");
  Serial.print(sensorThres);
  Serial.print(" | Current Value: ");
  Serial.println(data);

  if (data > sensorThres) {
    Blynk.logEvent("gas_alert", "Gas Leakage Detected");

    // Turn on the relay
    digitalWrite(relayPin, HIGH);

    // Turn on the buzzer
    digitalWrite(buzzerPin, HIGH);
  } else {
    // Keep the relay off if no smoke is detected
    digitalWrite(relayPin, LOW);

    // Turn off the buzzer if no smoke is detected
    digitalWrite(buzzerPin, LOW);
  }
}

void sendMotionSensorData() {
  int motionState = digitalRead(motionSensorPin);

  if (motionState == HIGH) {
    Serial.println("Motion detected!");
    // Turn on LED
    digitalWrite(ledPin, HIGH);
    // Update Blynk app
    Blynk.virtualWrite(V1, 1); // Motion Detected

    delay(5000); // Wait for 5 seconds

    // Turn off LED after 5 seconds
    digitalWrite(ledPin, LOW);
    Blynk.virtualWrite(V1, 0); // No Motion
  } else {
    Serial.println("No motion detected.");
    digitalWrite(ledPin, LOW); // Ensure LED is off
    Blynk.virtualWrite(V1, 0); // No Motion
  }
}

void setup() {
  // Set pin modes
  pinMode(smokeA0, INPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(motionSensorPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // Initialize serial communication at 115200 baud rate
  Serial.begin(115200);

  // Connect to Blynk
  Blynk.begin(auth, ssid, pass);

  // Set timer to read sensor data and send to Blynk
  timer.setInterval(500L, sendSmokeSensorData); // Updated interval to 0.5 second
  timer.setInterval(500L, sendMotionSensorData);
}

void loop() {
  // Run Blynk
  Blynk.run();
  // Run SimpleTimer
  timer.run();
}
