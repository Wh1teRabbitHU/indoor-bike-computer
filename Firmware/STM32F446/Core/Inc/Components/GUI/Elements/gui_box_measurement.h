#ifndef __GUI_BOX_MEASUREMENT_H_
#define __GUI_BOX_MEASUREMENT_H_

#include "lvgl.h"

typedef struct GUI_BoxMeasurement {
    lv_obj_t* box;
    lv_obj_t* avgValueLabel;
    lv_obj_t* curValueLabel;
} GUI_BoxMeasurement;

typedef struct GUI_BoxMeasurement_Config {
    lv_obj_t* screen;
    char* title;
    int32_t x;
    int32_t y;
    uint32_t bgColor;
} GUI_BoxMeasurement_Config;

GUI_BoxMeasurement GUI_BoxMeasurement_create(GUI_BoxMeasurement_Config* config);
void GUI_BoxMeasurement_setValue(GUI_BoxMeasurement* instance, char* avgVal, char* curVal);

#endif