#ifndef __BOX_MEASUREMENT_H_
#define __BOX_MEASUREMENT_H_

#include "lvgl.h"

typedef struct BoxMeasurement {
    lv_obj_t* box;
    lv_obj_t* avgValueLabel;
    lv_obj_t* curValueLabel;
} BoxMeasurement;

typedef struct BoxMeasurement_Config {
    lv_obj_t* screen;
    char* title;
    int32_t x;
    int32_t y;
    uint32_t bgColor;
} BoxMeasurement_Config;

BoxMeasurement BoxMeasurement_create(BoxMeasurement_Config* config);
void BoxMeasurement_setValue(BoxMeasurement* instance, char* avgVal, char* curVal);

#endif