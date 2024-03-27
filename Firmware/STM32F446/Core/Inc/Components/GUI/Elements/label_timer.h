#ifndef __LABEL_TIMER_H_
#define __LABEL_TIMER_H_

#include "lvgl.h"

typedef struct LabelTimer {
    lv_obj_t* timeLabel;
} LabelTimer;

typedef struct LabelTimer_Config {
    lv_obj_t* screen;
    char* name;
    int32_t x;
    int32_t y;
    uint32_t bgColor;
} LabelTimer_Config;

LabelTimer LabelTimer_create(LabelTimer_Config* config);
void LabelTimer_setValue(LabelTimer* instance, char* time);

#endif