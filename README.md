# IoT Based Motion Detector

An ESP32-based motion detection project that uses a PIR sensor and Blynk IoT Cloud to report motion events in real time. When motion is detected, the ESP32 sends a signal to the Blynk dashboard and prints the status to the Serial Monitor.

---

## Features

- Detects motion using a PIR sensor connected to an ESP32
- Sends motion status to Blynk IoT Cloud through Virtual Pin V0
- Prints motion events to the Serial Monitor
- Uses WiFi for wireless connectivity
- Includes PIR sensor stabilization time for reliable readings

---

## Components Used

- ESP32 development board
- PIR motion sensor
- Jumper wires
- Breadboard
- WiFi connection
- Blynk IoT account and dashboard

---

## How It Works

The ESP32 connects to WiFi and then to Blynk using the credentials defined in the sketch. The PIR sensor is read from GPIO 13.

- If motion is detected, the sketch sends `1` to V0 in Blynk and prints `Motion Detected!`
- If motion stops, the sketch sends `0` to V0 and prints `Motion Ended.`

The code also waits about 30 seconds after startup so the PIR sensor can stabilize before monitoring begins.

---

## Circuit Connection

| Component | ESP32 Pin |
|------------|-----------|
| PIR sensor VCC | 3.3V or 5V |
| PIR sensor GND | GND |
| PIR sensor OUT | GPIO 13 |

If your PIR module requires 5V, connect it to 5V. If it supports 3.3V, use 3.3V.

---

## Blynk Dashboard Setup

1. Create a new template in Blynk IoT.
2. Add a widget that can display the motion state.
3. Set the widget to use Virtual Pin V0.
4. Copy your:
   - BLYNK_TEMPLATE_ID
   - BLYNK_TEMPLATE_NAME
   - BLYNK_AUTH_TOKEN
5. Add these credentials to `main/secrets.h` (copy from [main/secrets.h.example](main/secrets.h.example)).

---

## Required Libraries

Install the following libraries in Arduino IDE:

- WiFi.h
- BlynkSimpleEsp32.h

The Blynk library can be installed from the Arduino Library Manager.

---

## Code Overview

The main logic is in [main/main.ino](main/main.ino). It reads the PIR sensor, tracks the previous motion state, and updates Blynk only when the state changes.

```cpp
if (val == HIGH) {
  if (pirState == LOW) {
    Serial.println("Motion Detected!");
    Blynk.virtualWrite(VPIN_MOTION, 1);
    pirState = HIGH;
  }
} else {
  if (pirState == HIGH) {
    Serial.println("Motion Ended.");
    Blynk.virtualWrite(VPIN_MOTION, 0);
    pirState = LOW;
  }
}
```

This prevents duplicate updates while the sensor remains in the same state.

---

## Setup Instructions

1. Open the project in Arduino IDE.
2. Install the required libraries (`WiFi.h`, `BlynkSimpleEsp32.h`).
3. Set up your private credentials:
   - Duplicate `main/secrets.h.example` and rename it to `main/secrets.h`.
   - Open `main/secrets.h` and enter your WiFi credentials and Blynk keys.
   - *(Note: `secrets.h` and `.env` are protected by `.gitignore` so your private keys are never committed to GitHub).*
4. Select your ESP32 board and upload the sketch from `main/main.ino`.
5. Power the PIR sensor and wait for the calibration delay to complete.
6. Open the Serial Monitor (baud rate: 115200) and Blynk dashboard to view motion events.

---

## Notes

- The sketch uses GPIO 13 for the PIR output.
- The Blynk virtual pin is V0.
- The PIR sensor needs a short warm-up period after power-on.

---

## License

This project is released under the [MIT License](LICENSE).