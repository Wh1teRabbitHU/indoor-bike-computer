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
    State_Global_get()->infoMessage = info;
}
void Bike_setError(char * error) {
    State_Global_get()->errorMessage = error;
}
void Bike_clearInfo(void) {
    State_Global_get()->infoMessage = NULL;
}
void Bike_clearError(void) {
    State_Global_get()->errorMessage = NULL;
}

void Bike_updateDifficulty(void) {
    difficulty                   = MCP3421_readMeasurement();
    State_Live_get()->difficulty = difficulty;
}

void Bike_updateRevolution(void) {
    if (revolutionTimer == NULL) {
        return;
    }

    volatile uint32_t elapsed = Bike_getElapsedTime();

    if (elapsed > 0) {
        rpm      = BIKE_CALCULATE_RPM(elapsed);
        speed    = BIKE_CALCULATE_SPEED(rpm);
        distance = BIKE_CALCULATE_DISTANCE(speed);
    }

    State_Live_get()->rpm      = rpm;
    State_Live_get()->distance = distance;
    State_Live_get()->speed    = speed;

    Bike_restartTimer();
}