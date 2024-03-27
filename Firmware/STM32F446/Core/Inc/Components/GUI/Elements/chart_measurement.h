#ifndef __CHART_MEASUREMENT_H_
#define __CHART_MEASUREMENT_H_

#include "lvgl.h"

typedef struct ChartMeasurement {
    lv_obj_t* chart;
    lv_chart_series_t* series1;
} ChartMeasurement;

typedef struct ChartMeasurement_Config {
    lv_obj_t* screen;
    char* title;
    int32_t x;
    int32_t y;
    uint32_t mainColor;
    uint32_t series1Color;
} ChartMeasurement_Config;

ChartMeasurement ChartMeasurement_create(ChartMeasurement_Config* config);
void ChartMeasurement_setValue(ChartMeasurement* instance, uint32_t value1);

#endif