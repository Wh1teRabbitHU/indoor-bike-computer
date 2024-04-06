#ifndef __STOPTIMER_H_
#define __STOPTIMER_H_

#include "main.h"
#include "state-handler.h"

typedef enum Stoptimer_State {
    STOPTIMER_STATE_STOPPED = 0,
    STOPTIMER_STATE_PAUSED = 1,
    STOPTIMER_STATE_RUNNING = 2
} Stoptimer_State;

void Stoptimer_start(void);
void Stoptimer_pause(void);
void Stoptimer_stop(void);
void Stoptimer_reset(void);
void Stoptimer_handleInterrupt(void);

#endif