#include "bike.h"

uint32_t lastRevolutionTimestamp = 0;
uint32_t difficulty = 15;
uint32_t rpm = 0;

void Bike_setInfo(char* info) { State_Global_get()->infoMessage = info; }
void Bike_setError(char* error) { State_Global_get()->errorMessage = error; }
void Bike_clearInfo(void) { State_Global_get()->infoMessage = NULL; }
void Bike_clearError(void) { State_Global_get()->errorMessage = NULL; }

void Bike_updateDifficulty(void) {
    difficulty = MCP3421_readMeasurement();
    State_Live_get()->difficulty = difficulty;
}

void Bike_updateRevolution(void) {
    uint32_t currentTimestamp = HAL_GetTick();

    if (lastRevolutionTimestamp > 0) {
        rpm = 60 / ((currentTimestamp - lastRevolutionTimestamp) / 1000.0);
    }

    lastRevolutionTimestamp = currentTimestamp;

    State_Live_get()->rpm = rpm;
}