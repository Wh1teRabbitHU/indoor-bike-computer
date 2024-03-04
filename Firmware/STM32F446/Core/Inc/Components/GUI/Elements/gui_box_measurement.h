#ifndef __GUI_BOX_MEASUREMENT_H_
#define __GUI_BOX_MEASUREMENT_H_

#include "lvgl.h"

typedef struct GUI_BoxMeasurement_t {
    lv_obj_t* box;
    lv_obj_t* valueLabel;
} GUI_BoxMeasurement_t;

GUI_BoxMeasurement_t GUI_BoxMeasurement_create(lv_obj_t* screen, int32_t x, int32_t y);
void GUI_BoxMeasurement_setValue(GUI_BoxMeasurement_t* instance, char* val);

#endif