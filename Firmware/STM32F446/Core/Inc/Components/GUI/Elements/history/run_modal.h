#ifndef __RUN_MODAL_H_
#define __RUN_MODAL_H_

#include "data.h"
#include "er_tft035.h"
#include "lvgl.h"
#include "macros.h"

#define RUN_MODAL_PADDING             10
#define RUN_MODAL_WIDTH               (ER_TFT035_SCREEN_WIDTH - (RUN_MODAL_PADDING * 2))
#define RUN_MODAL_HEIGHT              (ER_TFT035_SCREEN_HEIGHT - (RUN_MODAL_PADDING * 2))
#define RUN_MODAL_LABEL_WIDTH         RUN_MODAL_WIDTH
#define RUN_MODAL_LABEL_HEIGHT        24
#define RUN_MODAL_LABEL_GROUP_PADDING 4
#define RUN_MODAL_BUTTON_WIDTH        120
#define RUN_MODAL_BUTTON_HEIGHT       30
#define RUN_MODAL_BG_COLOR            0xFFFFFF

typedef enum RunModal_Button_t {
    RUN_MODAL_CLOSE  = 0,
    RUN_MODAL_DELETE = 1,
} RunModal_Button_t;

typedef struct RunModal {
    lv_obj_t * box;
    lv_obj_t * nameHeaderLabel;
    lv_obj_t * nameValueLabel;
    lv_obj_t * createdHeaderLabel;
    lv_obj_t * createdValueLabel;
    lv_obj_t * sessionLengthHeaderLabel;
    lv_obj_t * sessionLengthValueLabel;
    lv_obj_t * distanceHeaderLabel;
    lv_obj_t * distanceValueLabel;
    lv_obj_t * avgDifficultyHeaderLabel;
    lv_obj_t * avgDifficultyValueLabel;
    lv_obj_t * avgSpeedHeaderLabel;
    lv_obj_t * avgSpeedValueLabel;
    lv_obj_t * avgRpmHeaderLabel;
    lv_obj_t * avgRpmValueLabel;
    lv_obj_t * avgBpmHeaderLabel;
    lv_obj_t * avgBpmValueLabel;
    lv_obj_t * closeButton;
    lv_obj_t * deleteButton;
    uint8_t selectedButton;
    uint8_t open;
    uint8_t updated;
} RunModal;

typedef struct RunModal_Config {
    lv_obj_t * screen;
} RunModal_Config;

RunModal RunModal_create(RunModal_Config * config);
void RunModal_open(RunModal * instance);
void RunModal_close(RunModal * instance);
void RunModal_selectPrev(RunModal * instance);
void RunModal_selectNext(RunModal * instance);
uint8_t RunModal_execute(RunModal * instance);
uint8_t RunModal_stepOut(RunModal * instance);

void RunModal_update(RunModal * instance, Data_Run * run);

#endif