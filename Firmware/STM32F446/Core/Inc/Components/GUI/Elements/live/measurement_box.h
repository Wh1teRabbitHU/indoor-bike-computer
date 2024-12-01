#ifndef __MEASUREMENT_BOX_H_
#define __MEASUREMENT_BOX_H_

#include "lvgl.h"

typedef struct MeasurementBox {
    lv_obj_t * box;
    lv_obj_t * avgValueLabel;
    lv_obj_t * curValueLabel;
} MeasurementBox;

typedef struct MeasurementBox_Config {
    lv_obj_t * screen;
    char * title;
    int32_t x;
    int32_t y;
    uint32_t bgColor;
} MeasurementBox_Config;

MeasurementBox MeasurementBox_create(MeasurementBox_Config * config);
void MeasurementBox_setValue(MeasurementBox * instance, char * avgVal, char * curVal);

#endif