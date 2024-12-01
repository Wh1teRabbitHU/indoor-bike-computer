#ifndef __TIMER_BOX_H_
#define __TIMER_BOX_H_

#include "lvgl.h"

typedef struct TimerBox {
    lv_obj_t * box;
    lv_obj_t * timerLabel;
} TimerBox;

typedef struct TimerBox_Config {
    lv_obj_t * screen;
    char * name;
    int32_t x;
    int32_t y;
    uint32_t bgColor;
} TimerBox_Config;

TimerBox TimerBox_create(TimerBox_Config * config);
void TimerBox_setValue(TimerBox * instance, char * time);

#endif