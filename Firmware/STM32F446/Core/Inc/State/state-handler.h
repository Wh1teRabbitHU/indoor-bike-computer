#ifndef __STATE_HANDLER_H_
#define __STATE_HANDLER_H_

#include "stdint.h"
#include "stdio.h"

typedef enum State_Live_Session {
    APP_LIVESTATE_SESSION_STOPPED = 0,
    APP_LIVESTATE_SESSION_PAUSED = 1,
    APP_LIVESTATE_SESSION_RUNNING = 2
} State_Live_Session;

typedef struct State_Global {
    char* infoMessage;
    char* errorMessage;
    uint8_t updateLevel;  // This tells the GUI to update the menu level
} State_Global;

typedef struct State_Live {
    uint32_t difficulty;
    uint32_t speed;
    uint32_t rpm;
    uint32_t bpm;
    uint8_t updateChart;  //
    char* time;
    State_Live_Session sessionState;
} State_Live;

State_Global* State_Global_get(void);
State_Live* State_Live_get(void);
void State_Live_reset(void);

#endif