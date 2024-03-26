#ifndef INC_GUI_H_
#define INC_GUI_H_

#include "er_tft035.h"
#include "gui_screen_main.h"
#include "lvgl.h"
#include "stdio.h"

typedef enum GUI_Screen_t { GUI_SCREEN_MAIN, GUI_SCREEN_HISTORY, GUI_SCREEN_SETTINGS } GUI_Screen_t;

void GUI_init();
uint32_t GUI_tick();

void GUI_setInfo(char* info);
void GUI_setError(char* error);
void GUI_clearInfo(void);
void GUI_clearError(void);
void GUI_setDifficulty(uint32_t difficulty);
void GUI_setRpm(uint32_t rpm);
void GUI_setTime(RTC_TimeTypeDef* rtcTime);
void GUI_prevTab();
void GUI_nextTab();

#endif