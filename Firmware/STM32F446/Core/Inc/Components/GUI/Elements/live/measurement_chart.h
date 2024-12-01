#ifndef __MEASUREMENT_CHART_H_
#define __MEASUREMENT_CHART_H_

#include "lvgl.h"

typedef struct MeasurementChart {
    lv_obj_t * chart;
    lv_chart_series_t * series;
} MeasurementChart;

typedef struct MeasurementChart_Config {
    lv_obj_t * screen;
    char * title;
    int32_t x;
    int32_t y;
    uint32_t mainColor;
    uint32_t series1Color;
} MeasurementChart_Config;

MeasurementChart MeasurementChart_create(MeasurementChart_Config * config);
void MeasurementChart_setValue(MeasurementChart * instance, uint32_t value1);

#endif