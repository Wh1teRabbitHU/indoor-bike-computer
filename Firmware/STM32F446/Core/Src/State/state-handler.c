#include "state-handler.h"

static State_Global global = {.infoMessage = NULL, .errorMessage = NULL, .updateLevel = 0};

static State_Live live = {
    .difficulty = 0, .speed = 0, .rpm = 0, .bpm = 0, .updateChart = 0, .sessionState = APP_LIVESTATE_SESSION_STOPPED};

State_Global* State_Global_get(void) { return &global; }

State_Live* State_Live_get(void) { return &live; }

void State_Live_reset(void) {
    // No need to reset: difficulty, sessionState
    live.speed = 0;
    live.rpm = 0;
    live.bpm = 0;
    live.time = "00:00:00";

    live.updateChart = 1;
}