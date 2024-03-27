#ifndef __TABVIEW_MAIN_TAB_LIVE_H_
#define __TABVIEW_MAIN_TAB_LIVE_H_

#include "box_measurement.h"
#include "chart_measurement.h"
#include "label_timer.h"
#include "stdio.h"

typedef struct TabView_Main_Tab_Live_Config {
    lv_obj_t* tab;
} TabView_Main_Tab_Live_Config;

void TabView_Main_Tab_Live_init(TabView_Main_Tab_Live_Config* config);

void TabView_Main_Tab_Live_updateDifficulty(uint32_t difficulty);
void TabView_Main_Tab_Live_updateSpeed(uint32_t speed);
void TabView_Main_Tab_Live_updateRevolution(uint32_t rpm);
void TabView_Main_Tab_Live_updateHeartRate(uint32_t bpm);
void TabView_Main_Tab_Live_updateChart(uint8_t updateChart);
void TabView_Main_Tab_Live_updateTimer(char* time);

#endif