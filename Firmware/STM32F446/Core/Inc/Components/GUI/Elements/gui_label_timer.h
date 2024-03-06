#ifndef __GUI_LABEL_TIMER_H_
#define __GUI_LABEL_TIMER_H_

#include "lvgl.h"

typedef struct GUI_LabelTimer {
    lv_obj_t* timeLabel;
} GUI_LabelTimer;

typedef struct GUI_LabelTimer_Config {
    lv_obj_t* screen;
    char* name;
    int32_t x;
    int32_t y;
    uint32_t bgColor;
} GUI_LabelTimer_Config;

GUI_LabelTimer GUI_LabelTimer_create(GUI_LabelTimer_Config* config);
void GUI_LabelTimer_setValue(GUI_LabelTimer* instance, char* time);

#endif