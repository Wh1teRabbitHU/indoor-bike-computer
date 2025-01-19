#include "stoptimer.h"

extern RTC_HandleTypeDef hrtc;

static char timeBuffer[15];
static Stoptimer_State state   = STOPTIMER_STATE_STOPPED;
static RTC_DateTypeDef rtcDate = {0};
static RTC_TimeTypeDef rtcTime = {0};

PRIVATE void Stoptimer_updateRun(void) {
    sprintf(timeBuffer, "%02d:%02d:%02d", rtcTime.Hours, rtcTime.Minutes, rtcTime.Seconds);

    State_updateRun(timeBuffer);
}

void Stoptimer_getTime(void) {
    HAL_RTC_GetTime(&hrtc, &rtcTime, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &rtcDate, RTC_FORMAT_BIN);
}

void Stoptimer_setTime(void) {
    HAL_RTC_SetTime(&hrtc, &rtcTime, RTC_FORMAT_BIN);
}

void Stoptimer_start(void) {
    Stoptimer_setTime();

    state = STOPTIMER_STATE_RUNNING;
}

void Stoptimer_pause(void) {
    state = STOPTIMER_STATE_PAUSED;
}

void Stoptimer_stop(void) {
    state = STOPTIMER_STATE_STOPPED;

    Stoptimer_reset();
}

void Stoptimer_reset(void) {
    rtcTime.Hours   = 0;
    rtcTime.Minutes = 0;
    rtcTime.Seconds = 0;

    Stoptimer_setTime();
}

void Stoptimer_handleInterrupt(void) {
    if (state != STOPTIMER_STATE_RUNNING) {
        return;
    }

    Stoptimer_getTime();
    Stoptimer_updateRun();
}