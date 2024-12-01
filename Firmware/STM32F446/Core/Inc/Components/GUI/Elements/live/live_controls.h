#ifndef __LIVE_CONTROLS_H_
#define __LIVE_CONTROLS_H_

#include "lvgl.h"
#include "macros.h"

#define LIVE_CONTROLS_BUTTON_COUNT 3

typedef enum LiveControls_Button_t {
    LIVE_CONTROLS_START = 0,
    LIVE_CONTROLS_END   = 1,
    LIVE_CONTROLS_RESET = 2,
} LiveControls_Button_t;

typedef struct LiveControls {
    lv_obj_t * buttonMatrix;
    LiveControls_Button_t selected;
    uint8_t enabled[LIVE_CONTROLS_BUTTON_COUNT];
} LiveControls;

typedef struct LiveControls_Config {
    lv_obj_t * screen;
    int32_t x;
    int32_t y;
    uint32_t bgColor;
} LiveControls_Config;

LiveControls LiveControls_create(LiveControls_Config * config);
void LiveControls_updateState(LiveControls * instance);
void LiveControls_updateBtnText(uint8_t index, char * text);

#endif