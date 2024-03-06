#ifndef __GUI_CHART_MEASUREMENT_H_
#define __GUI_CHART_MEASUREMENT_H_

#include "lvgl.h"

typedef struct GUI_ChartMeasurement {
    lv_obj_t* container;
    lv_obj_t* chart;
    lv_chart_series_t* series1;
} GUI_ChartMeasurement;

typedef struct GUI_ChartMeasurement_Config {
    lv_obj_t* screen;
    char* title;
    int32_t x;
    int32_t y;
    uint32_t mainColor;
    uint32_t series1Color;
} GUI_ChartMeasurement_Config;

GUI_ChartMeasurement GUI_ChartMeasurement_create(GUI_ChartMeasurement_Config* config);
void GUI_ChartMeasurement_setValue(GUI_ChartMeasurement* instance, uint32_t value1);

#endif