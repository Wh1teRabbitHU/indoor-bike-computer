#include <Arduino.h>

void setup() {
    Serial.begin(115200);
    Serial2.begin(115200);

    delay(10);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("ESP32 is ready");
    Serial.println();
    Serial.println();
}

char logBuffer[32] = {'\0'};
char uartBuffer[16] = {'\0'};
uint32_t counter = 0;
uint8_t bufferPointer = 0;

void loop() {
    while (Serial2.available()) {
        uartBuffer[bufferPointer++] = (char)Serial2.read();
    }

    if (bufferPointer > 0) {
        sprintf(logBuffer, "[%09lu] %s", counter++, uartBuffer);
        Serial.println(logBuffer);
        bufferPointer = 0;
    }
}
