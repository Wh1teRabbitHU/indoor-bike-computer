#ifndef __LABEL_LOADING_H_
#define __LABEL_LOADING_H_

#include "er_tft035.h"
#include "lvgl.h"

#define LABEL_LOADING_WIDTH 300
#define LABEL_LOADING_HEIGHT 30

typedef struct LabelLoading {
    lv_obj_t* loadingBox;
} LabelLoading;

typedef struct LabelLoading_Config {
    lv_obj_t* screen;
    uint32_t bgColor;
} LabelLoading_Config;

LabelLoading LabelLoading_create(LabelLoading_Config* config);
void LabelLoading_show(LabelLoading* config);
void LabelLoading_hide(LabelLoading* config);

#endif