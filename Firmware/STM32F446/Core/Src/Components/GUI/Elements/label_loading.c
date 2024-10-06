#include "label_loading.h"

LabelLoading LabelLoading_create(LabelLoading_Config* config) {
    LabelLoading loadingInstance = {};

    lv_obj_t* box = lv_obj_create(config->screen);

    lv_obj_align(box, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_set_width(box, LABEL_LOADING_WIDTH);
    lv_obj_set_height(box, LABEL_LOADING_HEIGHT);
    lv_obj_set_pos(box, (ER_TFT035_SCREEN_WIDTH / 2) - (LABEL_LOADING_WIDTH / 2),
                   (ER_TFT035_SCREEN_HEIGHT / 2) - (LABEL_LOADING_HEIGHT / 2));
    lv_obj_set_style_pad_all(box, 5, LV_PART_MAIN);
    lv_obj_remove_flag(box, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(box, lv_color_hex(config->bgColor), LV_PART_MAIN);

    lv_obj_t* loadingLabel = lv_label_create(box);

    lv_obj_set_style_text_color(loadingLabel, lv_color_hex(0x000000), LV_PART_MAIN);
    // lv_obj_align(loadingLabel, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_width(loadingLabel, LABEL_LOADING_WIDTH);
    lv_obj_set_style_text_align(loadingLabel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_text(loadingLabel, "Loading data...");

    loadingInstance.loadingBox = box;

    LabelLoading_hide(&loadingInstance);

    return loadingInstance;
}

void LabelLoading_show(LabelLoading* instance) { lv_obj_clear_flag(instance->loadingBox, LV_OBJ_FLAG_HIDDEN); }

void LabelLoading_hide(LabelLoading* instance) { lv_obj_add_flag(instance->loadingBox, LV_OBJ_FLAG_HIDDEN); }