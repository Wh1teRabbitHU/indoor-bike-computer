#include "bike.h"

static uint32_t difficulty                 = 15;
static uint32_t rpm                        = 0;
static uint32_t distance                   = 0;
static uint32_t speed                      = 0;
static TIM_HandleTypeDef * revolutionTimer = NULL;

/**
 * @brief This method returns the time elapsed since the last revolution
 *
 * @return the elapsed time in milliseconds
 */
PRIVATE uint32_t Bike_getElapsedTime(void) {
    return revolutionTimer->Instance->CNT / 10;
}

PRIVATE void Bike_restartTimer(void) {
    revolutionTimer->Instance->CR1 &= ~TIM_CR1_UDIS;
    revolutionTimer->Instance->EGR = TIM_EGR_UG;
    revolutionTimer->Instance->CR1 |= TIM_CR1_UDIS;

    HAL_TIM_Base_Start(revolutionTimer);
}

void Bike_init(TIM_HandleTypeDef * _revolutionTimer) {
    revolutionTimer = _revolutionTimer;
}

void Bike_setInfo(char * info) {
    State_getGlobal()->infoMessage = info;
}
void Bike_setError(char * error) {
    State_getGlobal()->errorMessage = error;
}
void Bike_clearInfo(void) {
    State_getGlobal()->infoMessage = NULL;
}
void Bike_clearError(void) {
    State_getGlobal()->errorMessage = NULL;
}

void Bike_updateDifficulty(void) {
    difficulty                  = MCP3421_readMeasurement();
    State_getLive()->difficulty = difficulty;
}

void Bike_updateRevolution(void) {
    if (revolutionTimer == NULL) {
        return;
    }

    State_getLive()->pedalRotating = 1;
    State_getLive()->haltCounter   = 0;

    uint32_t elapsed = Bike_getElapsedTime();

    if (elapsed > 0) {
        rpm      = BIKE_CALCULATE_RPM(elapsed);
        speed    = BIKE_CALCULATE_SPEED(rpm);
        distance = BIKE_CALCULATE_DISTANCE(speed);
    }

    State_getLive()->rpm      = rpm;
    State_getLive()->distance = distance;
    State_getLive()->speed    = speed;

    Bike_restartTimer();
}