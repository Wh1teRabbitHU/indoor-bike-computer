#include "bike.h"

uint32_t lastRevolutionTimestamp = 0;
uint32_t difficulty = 15;
uint32_t rpm = 0;

char textBuffer[32];

void Bike_updateDifficulty(void) {
    difficulty = MCP3421_readMeasurement();
    GUI_setDifficulty(difficulty);
}

void Bike_updateRevolution(void) {
    uint32_t currentTimestamp = HAL_GetTick();

    if (lastRevolutionTimestamp > 0) {
        rpm = 60 / ((currentTimestamp - lastRevolutionTimestamp) / 1000.0);
    }

    lastRevolutionTimestamp = currentTimestamp;

    GUI_setRpm(rpm);
}