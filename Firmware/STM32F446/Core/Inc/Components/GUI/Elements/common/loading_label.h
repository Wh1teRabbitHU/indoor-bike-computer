#ifndef __LOADING_LABEL_H_
#define __LOADING_LABEL_H_

#include "er_tft035.h"
#include "lvgl.h"

#define LOADING_LABEL_WIDTH  300
#define LOADING_LABEL_HEIGHT 50
#define LOADING_LABEL_POS_X  (ER_TFT035_SCREEN_WIDTH / 2) - (LOADING_LABEL_WIDTH / 2)
#define LOADING_LABEL_POS_Y  (ER_TFT035_SCREEN_HEIGHT / 2) - (LOADING_LABEL_HEIGHT / 2)

typedef struct LoadingLabel {
    lv_obj_t * box;
    uint8_t visible;
} LoadingLabel;

typedef struct LoadingLabel_Config {
    lv_obj_t * screen;
    uint32_t bgColor;
} LoadingLabel_Config;

LoadingLabel LoadingLabel_create(LoadingLabel_Config * config);
void LoadingLabel_show(LoadingLabel * instance);
void LoadingLabel_hide(LoadingLabel * instance);

#endif