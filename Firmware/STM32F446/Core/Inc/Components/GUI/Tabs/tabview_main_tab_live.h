#ifndef __TABVIEW_MAIN_TAB_LIVE_H_
#define __TABVIEW_MAIN_TAB_LIVE_H_

#include "box_measurement.h"
#include "chart_measurement.h"
#include "control_live.h"
#include "data.h"
#include "label_timer.h"
#include "macros.h"
#include "state-handler.h"
#include "stdio.h"
#include "stoptimer.h"

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
void TabView_Main_Tab_Live_updateControl(void);

void TabView_Main_Tab_Live_stepIn();
void TabView_Main_Tab_Live_stepOut();

// Control handlers
void TabView_Main_Tab_Live_execute(void);
void TabView_Main_Tab_Live_handlePrev(void);
void TabView_Main_Tab_Live_handleNext(void);

#endif