#include "bike.h"

uint32_t lastRevolutionTimestamp = 0;
uint32_t difficulty = 15;
uint32_t rpm = 0;

static char timeBuffer[15];

void Bike_setInfo(char* info) { ScreenMain_getState()->infoMessage = info; }
void Bike_setError(char* error) { ScreenMain_getState()->errorMessage = error; }
void Bike_clearInfo(void) { ScreenMain_getState()->infoMessage = NULL; }
void Bike_clearError(void) { ScreenMain_getState()->errorMessage = NULL; }
void Bike_setTime(RTC_TimeTypeDef* rtcTime) {
    sprintf(timeBuffer, "%02d:%02d:%02d", rtcTime->Hours, rtcTime->Minutes, rtcTime->Seconds);

    ScreenMain_getState()->time = timeBuffer;
    ScreenMain_getState()->updateChart = 1;
}

void Bike_updateDifficulty(void) {
    difficulty = MCP3421_readMeasurement();
    ScreenMain_getState()->difficulty = difficulty;
}

void Bike_updateRevolution(void) {
    uint32_t currentTimestamp = HAL_GetTick();

    if (lastRevolutionTimestamp > 0) {
        rpm = 60 / ((currentTimestamp - lastRevolutionTimestamp) / 1000.0);
    }

    lastRevolutionTimestamp = currentTimestamp;

    ScreenMain_getState()->rpm = rpm;
}