#ifndef __CONTROL_LIVE_H_
#define __CONTROL_LIVE_H_

#include "lvgl.h"
#include "macros.h"

#define CONTROLLIVE_BUTTON_COUNT 3

typedef enum ControlLive_Button_t {
    CONTROLLIVE_START = 0,
    CONTROLLIVE_END = 1,
    CONTROLLIVE_RESET = 2,
} ControlLive_Button_t;

typedef struct ControlLive {
    lv_obj_t* buttonMatrix;
    ControlLive_Button_t selected;
    uint8_t enabled[CONTROLLIVE_BUTTON_COUNT];
} ControlLive;

typedef struct ControlLive_Config {
    lv_obj_t* screen;
    int32_t x;
    int32_t y;
    uint32_t bgColor;
} ControlLive_Config;

ControlLive ControlLive_create(ControlLive_Config* config);
void ControlLive_updateState(ControlLive* instance);

#endif