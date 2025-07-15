#define BLYNK_TEMPLATE_ID "TMPL2EWJ_IC66"
#define BLYNK_TEMPLATE_NAME "RFID NodeMCU ESP8266"
#define BLYNK_AUTH_TOKEN "yL3YPYDvcWC_CQ3NAGY79fwiFDY16nBo"

// Your WiFi credentials
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "MdNabilAhmed";  // Type your WiFi name
char pass[] = "Nabil12345";    // Type your WiFi password

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SPI.h>
#include <MFRC522.h>  

#define RST_PIN         D3  // Reset pin for NodeMCU ESP8266
#define SS_PIN          D8  // Slave Select pin for NodeMCU ESP8266
#define RELAY_PIN       10  // Relay control pin
#define LED_PIN         D0  // LED pin to indicate access denied

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

// Registered card UIDs
byte registeredUID1[] = {0x63, 0xF4, 0x3D, 0x1A}; // Replace with your first registered card UID

void setup() {
    Serial.begin(9600);  // Initialize serial communications with the PC
    SPI.begin();         // Init SPI bus
    mfrc522.PCD_Init();  // Init MFRC522
    Serial.println(F("Scan RFID tag to see UID..."));

    pinMode(RELAY_PIN, OUTPUT);  // Set relay pin as an output
    pinMode(LED_PIN, OUTPUT);    // Set LED pin as an output
    digitalWrite(RELAY_PIN, HIGH); // Initially turn relay off
    digitalWrite(LED_PIN, LOW);  // Initially turn LED off

    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);  // Initialize Blynk
    Blynk.virtualWrite(V0, "System Ready"); // Notify Blynk that the system is ready
}

void loop() {
    Blynk.run();  // Run Blynk

    // Check if no new card is present on the sensor/reader
    if (!mfrc522.PICC_IsNewCardPresent()) {
        Blynk.virtualWrite(V4, 0); // Send signal to gauge widget for no card detected
        return;
    }

    // Select one of the cards
    if (!mfrc522.PICC_ReadCardSerial()) {
        Blynk.virtualWrite(V4, 0); // Send signal to gauge widget for no card detected
        return;
    }

    // Convert the UID to a single value for comparison
    unsigned long uidValue = 0;
    for (byte i = 0; i < mfrc522.uid.size; i++) {
        uidValue = uidValue * 256 + mfrc522.uid.uidByte[i];
    }

    // Check if the detected UID matches the registered UID
    if (uidValue == convertUIDToValue(registeredUID1)) {
        digitalWrite(RELAY_PIN, LOW);  // Turn relay on
        Serial.println(F("Access Granted: Registered card detected, relay turned on."));
        Blynk.virtualWrite(V1, "Access Granted: Relay turned on");
        Blynk.virtualWrite(V5, 100); // Update gauge widget for access granted
        delay(5000);  // Keep relay on for 5 seconds
        digitalWrite(RELAY_PIN, HIGH);   // Turn relay off
        Serial.println(F("Relay turned off after 5 seconds."));
        Blynk.virtualWrite(V1, "Relay turned off after 5 seconds");
        Blynk.virtualWrite(V5, 0); // Reset gauge widget
    } else {
        digitalWrite(LED_PIN, HIGH);  // Turn LED on
        Serial.println(F("Access Denied: Unregistered card detected, LED turned on."));
        Blynk.virtualWrite(V1, "Access Denied: Relay turned off");
        Blynk.virtualWrite(V6, uidValue); // Send UID value to additional gauge widget for access denied

        // Keep LED on for 5 seconds
        delay(5000);

        digitalWrite(LED_PIN, LOW);  // Turn LED off
        Serial.println(F("LED turned off after 5 seconds."));
        Blynk.virtualWrite(V1, "LED turned off after 5 seconds");
        Blynk.virtualWrite(V6, 0); // Reset additional gauge widget
    }

    // Reset the gauge widgets to 0
    Blynk.virtualWrite(V3, 0);
    Blynk.virtualWrite(V4, 0);
}

// Function to check if the UID is registered
unsigned long convertUIDToValue(byte *uid) {
    unsigned long value = 0;
    for (byte i = 0; i < 4; i++) {
        value = value * 256 + uid[i];
    }
    return value;
}

// Blynk function to receive data from the app
BLYNK_WRITE(V2) {
    int pinValue = param.asInt();
    Serial.println(F("Received data from Blynk: "));
    Serial.println(pinValue);

    // Perform actions based on received data
    if (pinValue == 1) {
        // Example: Turn on the relay
        digitalWrite(RELAY_PIN, LOW);
        Blynk.virtualWrite(V1, "Relay turned on from Blynk");
        delay(5000); // Keep relay on for 5 seconds
        digitalWrite(RELAY_PIN, HIGH); // Turn relay off
        Serial.println(F("Relay turned off after 5 seconds."));
        Blynk.virtualWrite(V1, "Relay turned off after 5 seconds");
    } else if (pinValue == 0) {
        // Example: Turn off the relay
        digitalWrite(RELAY_PIN, HIGH);
        Blynk.virtualWrite(V1, "Relay turned off from Blynk");
    }
}
