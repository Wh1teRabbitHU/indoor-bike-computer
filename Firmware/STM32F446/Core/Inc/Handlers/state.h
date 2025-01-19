#ifndef __STATE_H_
#define __STATE_H_

#include "bike.h"
#include "data.h"
#include "stdint.h"
#include "stdio.h"

#define STATE_SIGNAL_TIMEOUT_THRESHOLD 3

typedef enum State_Live_Session {
    APP_LIVESTATE_SESSION_STOPPED = 0,
    APP_LIVESTATE_SESSION_PAUSED  = 1,
    APP_LIVESTATE_SESSION_RUNNING = 2
} State_Live_Session;

typedef struct State_Global {
    char * infoMessage;
    char * errorMessage;
    uint8_t updateLevel; // This tells the GUI to update the menu level
} State_Global;

typedef struct State_Live {
    uint32_t difficulty;
    uint32_t speed;
    uint32_t distance;
    uint32_t rpm;
    uint32_t bpm;
    uint8_t updateChart;
    char * time;
    State_Live_Session sessionState;
    uint8_t running;
    uint8_t pedalRotating;
    uint8_t haltCounter; // This is a signal tracker, helping to auto determine when the user stopped rotating the pedals
    Data_Run liveRun;
    Data_RunMeasurement lastMeasurement;
} State_Live;

State_Global * State_getGlobal(void);
State_Live * State_getLive(void);

void State_startRun();
void State_pauseRun();
void State_updateRun(char * timestamp);
void State_stopRun(void);

#endif