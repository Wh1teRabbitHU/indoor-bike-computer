#ifndef __MODAL_RUN_DETAILS_H_
#define __MODAL_RUN_DETAILS_H_

#include "data.h"
#include "er_tft035.h"
#include "lvgl.h"
#include "macros.h"

#define MODAL_RUN_DETAILS_PADDING             10
#define MODAL_RUN_DETAILS_WIDTH               (ER_TFT035_SCREEN_WIDTH - (MODAL_RUN_DETAILS_PADDING * 2))
#define MODAL_RUN_DETAILS_HEIGHT              (ER_TFT035_SCREEN_HEIGHT - (MODAL_RUN_DETAILS_PADDING * 2))
#define MODAL_RUN_DETAILS_LABEL_WIDTH         MODAL_RUN_DETAILS_WIDTH
#define MODAL_RUN_DETAILS_LABEL_HEIGHT        24
#define MODAL_RUN_DETAILS_LABEL_GROUP_PADDING 4
#define MODAL_RUN_DETAILS_BUTTON_WIDTH        120
#define MODAL_RUN_DETAILS_BUTTON_HEIGHT       30
#define MODAL_RUN_DETAILS_BG_COLOR            0xFFFFFF

typedef struct ModalRunDetails {
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
    uint8_t open;
    uint8_t updated;
} ModalRunDetails;

typedef struct ModalRunDetails_Config {
    lv_obj_t * screen;
} ModalRunDetails_Config;

ModalRunDetails ModalRunDetails_create(ModalRunDetails_Config * config);
void ModalRunDetails_open(ModalRunDetails * instance);
void ModalRunDetails_close(ModalRunDetails * instance);
void ModalRunDetails_update(ModalRunDetails * instance, Data_Run * run);

#endif