#ifndef INC_GUI_H_
#define INC_GUI_H_

#include "er_tft035.h"
#include "lvgl.h"
#include "stdio.h"

typedef struct GUI_mainScreenState {
    char* infoMessage;
    char* errorMessage;
    uint32_t difficulty;
    uint32_t rpm;
} GUI_mainScreenState;

void GUI_init();
uint32_t GUI_tick();

void GUI_setInfo(char* info);
void GUI_setError(char* error);
void GUI_setDifficulty(uint32_t difficulty);
void GUI_setRpm(uint32_t rpm);

#endif