#ifndef __MAIN_TABVIEW_LIVE_H_
#define __MAIN_TABVIEW_LIVE_H_

#include "data.h"
#include "live_controls.h"
#include "macros.h"
#include "measurement_box.h"
#include "measurement_chart.h"
#include "state.h"
#include "stdio.h"
#include "stoptimer.h"
#include "timer_box.h"

typedef struct MainTabviewLive_Config {
    lv_obj_t * tab;
} MainTabviewLive_Config;

void MainTabviewLive_init(MainTabviewLive_Config * config);

void MainTabviewLive_updateDifficulty(uint32_t current, uint32_t average);
void MainTabviewLive_updateSpeed(uint32_t current, uint32_t average);
// void MainTabviewLive_updateRevolution(uint32_t current, uint32_t average);
void MainTabviewLive_updateDistance(uint32_t distance);
void MainTabviewLive_updateHeartRate(uint32_t current, uint32_t average);
void MainTabviewLive_updateChart(uint8_t updateChart);
void MainTabviewLive_updateTimer(char * time);
void MainTabviewLive_updateControl(void);

void MainTabviewLive_stepIn();
void MainTabviewLive_stepOut();

// Control handlers
void MainTabviewLive_execute(void);
void MainTabviewLive_handlePrev(void);
void MainTabviewLive_handleNext(void);

#endif