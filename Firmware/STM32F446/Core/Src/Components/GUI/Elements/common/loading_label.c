#include "loading_label.h"

LoadingLabel LoadingLabel_create(LoadingLabel_Config * config) {
    LoadingLabel loadingInstance = {};

    lv_obj_t * box = lv_obj_create(config->screen);

    lv_obj_align(box, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_set_width(box, LOADING_LABEL_WIDTH);
    lv_obj_set_height(box, LOADING_LABEL_HEIGHT);
    lv_obj_set_pos(box, LOADING_LABEL_POS_X, LOADING_LABEL_POS_Y);
    lv_obj_set_style_pad_all(box, 5, LV_PART_MAIN);
    lv_obj_remove_flag(box, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(box, lv_color_hex(config->bgColor), LV_PART_MAIN);

    lv_obj_t * loadingLabel = lv_label_create(box);

    lv_obj_set_style_text_color(loadingLabel, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_align(loadingLabel, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_width(loadingLabel, LOADING_LABEL_WIDTH);
    lv_obj_set_style_text_align(loadingLabel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_text(loadingLabel, "Loading data...");

    loadingInstance.box = box;

    LoadingLabel_hide(&loadingInstance);

    return loadingInstance;
}

void LoadingLabel_show(LoadingLabel * instance) {
    instance->visible = 1;

    lv_obj_clear_flag(instance->box, LV_OBJ_FLAG_HIDDEN);
}

void LoadingLabel_hide(LoadingLabel * instance) {
    instance->visible = 0;

    lv_obj_add_flag(instance->box, LV_OBJ_FLAG_HIDDEN);
}