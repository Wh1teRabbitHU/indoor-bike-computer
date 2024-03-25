#ifndef __GUI_MAIN_SCREEN_H_
#define __GUI_MAIN_SCREEN_H_

#include "er_tft035.h"
#include "gui_box_measurement.h"
#include "gui_chart_measurement.h"
#include "gui_label_timer.h"
#include "gui_tab_main.h"
#include "lvgl.h"
#include "stdio.h"

#define GUI_MAINSCREEN_BGCOLOR 0x000000

typedef struct GUI_MainScreen_State {
    char* infoMessage;
    char* errorMessage;
    uint32_t difficulty;
    uint32_t speed;
    uint32_t rpm;
    uint32_t bpm;
    uint8_t updateChart;
    GUI_TabMain_t activeTab;
    char* time;
} GUI_MainScreen_State;

void GUI_MainScreen_init(void);
void GUI_MainScreen_updateStates(void);
void GUI_MainScreen_showNextChartValue();

GUI_MainScreen_State* GUI_MainScreen_getState(void);

#endif