/*************************************************************
  ESP32 PIR Motion Detector with Blynk IoT Cloud
  - Prints motion status on Serial Monitor
  - Turns ON/OFF LED widget in Blynk Dashboard
*************************************************************/

// Load credentials from secrets header (keep private, do not commit secrets.h to GitHub)
#if __has_include("secrets.h")
  #include "secrets.h"
#else
  #warning "secrets.h not found. Please copy secrets.h.example to secrets.h and update your credentials."
  #define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
  #define BLYNK_TEMPLATE_NAME "YOUR_TEMPLATE_NAME"
  #define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN"
  #define WIFI_SSID "YOUR_WIFI_SSID"
  #define WIFI_PASS "YOUR_WIFI_PASSWORD"
#endif

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// WiFi credentials
char ssid[] = WIFI_SSID;
char pass[] = WIFI_PASS;

// PIR sensor pin
#define PIR_PIN 13

// Virtual pin in Blynk
#define VPIN_MOTION V0

// Variables to track motion state
int pirState = LOW;
int val = 0;

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  delay(1000);

  // Configure PIR pin
  pinMode(PIR_PIN, INPUT);

  // Connect to WiFi and Blynk
  Serial.println("Connecting to WiFi...");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  Serial.println("Connected to WiFi and Blynk!");
  Serial.println("PIR Motion Sensor Initializing...");
  Serial.println("Please wait 30–60 seconds for calibration.");
  
  delay(30000);  // PIR sensor stabilization time

  Serial.println("Calibration complete.");
  Serial.println("System Ready! Monitoring for motion...");
  Serial.println("--------------------------------------");
}

void loop() {
  // Run Blynk
  Blynk.run();

  // Read PIR sensor output
  val = digitalRead(PIR_PIN);

  if (val == HIGH) {
    // Motion detected
    if (pirState == LOW) {
      Serial.println("🚶 Motion Detected!");
      Blynk.virtualWrite(VPIN_MOTION, 1);  // Turn ON LED in Blynk
      pirState = HIGH;
    }
  } else {
    // Motion ended
    if (pirState == HIGH) {
      Serial.println("✅ Motion Ended.");
      Blynk.virtualWrite(VPIN_MOTION, 0);  // Turn OFF LED in Blynk
      pirState = LOW;
    }
  }

  delay(100);  // Stability delay
}