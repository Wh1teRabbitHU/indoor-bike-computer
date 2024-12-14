#ifndef __MEASUREMENT_BOX_H_
#define __MEASUREMENT_BOX_H_

#include "lvgl.h"

#define MEASUREMENT_BOX_WIDTH   145
#define MEASUREMENT_BOX_HEIGHT  100
#define MEASUREMENT_BOX_PADDING 5

typedef struct MeasurementBoxSingle {
    lv_obj_t * box;
    lv_obj_t * valueLabel;
} MeasurementBoxSingle;

typedef struct MeasurementBoxDual {
    lv_obj_t * box;
    lv_obj_t * avgValueLabel;
    lv_obj_t * curValueLabel;
} MeasurementBoxDual;

typedef struct MeasurementBox_Config {
    lv_obj_t * screen;
    char * title;
    int32_t x;
    int32_t y;
    uint32_t bgColor;
} MeasurementBox_Config;

MeasurementBoxSingle MeasurementBox_createSingle(MeasurementBox_Config * config);
MeasurementBoxDual MeasurementBox_createDual(MeasurementBox_Config * config);
void MeasurementBox_setSingleValue(MeasurementBoxSingle * instance, char * val);
void MeasurementBox_setDualValue(MeasurementBoxDual * instance, char * curVal, char * avgVal);

#endif