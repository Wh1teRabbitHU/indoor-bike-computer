#include "app-state.h"

static App_State state = {.infoMessage = NULL,
                          .errorMessage = NULL,
                          .difficulty = 0,
                          .speed = 0,
                          .rpm = 0,
                          .bpm = 0,
                          .updateChart = 0,
                          .updateLevel = 0};

App_State* App_State_get(void) { return &state; }