#include <Arduino.h>
#include <HardwareSerial.h>

HardwareSerial ESP32Serial(1);

String message;

void setup() {
    ESP32Serial.begin(115200);
    // ESP32Serial.begin(115200, SERIAL_8N1, 5, 6);
    ESP32Serial.print("Initialised!");
    delay(100);
}

void loop() { ESP32Serial.println("PingPing"); }
