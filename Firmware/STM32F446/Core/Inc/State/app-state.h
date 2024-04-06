#ifndef __APP_STATE_H_
#define __APP_STATE_H_

#include "stdint.h"
#include "stdio.h"

typedef struct App_State {
    char* infoMessage;
    char* errorMessage;
    uint32_t difficulty;
    uint32_t speed;
    uint32_t rpm;
    uint32_t bpm;
    uint8_t updateChart;
    uint8_t updateLevel;
    char* time;
} App_State;

App_State* App_State_get(void);

#endif