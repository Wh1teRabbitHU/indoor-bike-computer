#include "bike.h"

static uint32_t lastRevolutionTimestamp = 0;
static uint32_t difficulty = 15;
static uint32_t rpm = 0;
static uint32_t distance = 0;
static uint32_t speed = 0;

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

    if (lastRevolutionTimestamp > 0 && currentTimestamp != lastRevolutionTimestamp) {
        rpm = 60 / ((currentTimestamp - lastRevolutionTimestamp) / 1000.0);
        speed = rpm * BIKE_WHEEL_SPEED_RATIO;  // km/h * 100
        distance = (speed * 10) / 60 / 60;     // km/h * 100 -> m/h -> m/min -> m/s
    }

    lastRevolutionTimestamp = currentTimestamp;

    State_Live_get()->rpm = rpm;
    State_Live_get()->distance = distance;
    State_Live_get()->speed = speed;
}