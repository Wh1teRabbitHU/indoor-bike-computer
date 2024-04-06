#include "state-handler.h"

static State_Global global = {.infoMessage = NULL, .errorMessage = NULL};

static State_Live live = {.difficulty = 0,
                          .speed = 0,
                          .rpm = 0,
                          .bpm = 0,
                          .updateChart = 0,
                          .updateLevel = 0,
                          .liveState = APP_LIVESTATE_SESSION_STOPPED};

State_Global* State_Global_get(void) { return &global; }
State_Live* State_Live_get(void) { return &live; }