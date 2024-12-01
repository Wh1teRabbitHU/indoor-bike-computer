#include "timer_box.h"

TimerBox TimerBox_create(TimerBox_Config * config) {
    TimerBox timerInstance = {};

    lv_obj_t * box = lv_obj_create(config->screen);

    lv_obj_align(box, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_set_width(box, 300);
    lv_obj_set_height(box, 30);
    lv_obj_set_pos(box, config->x, config->y);
    lv_obj_set_style_pad_all(box, 5, LV_PART_MAIN);
    lv_obj_remove_flag(box, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(box, lv_color_hex(config->bgColor), LV_PART_MAIN);

    lv_obj_t * label = lv_label_create(box);

    lv_obj_set_style_text_color(label, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_align(label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_width(label, 140);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_text(label, config->name);

    lv_obj_t * timerLabel = lv_label_create(box);

    lv_obj_set_style_text_color(timerLabel, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_align(timerLabel, LV_ALIGN_RIGHT_MID, 0, 0);
    lv_obj_set_width(timerLabel, 150);
    lv_obj_set_style_text_align(timerLabel, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);
    lv_label_set_text(timerLabel, "00:00:00");

    timerInstance.box       = box;
    timerInstance.timerLabel = timerLabel;

    return timerInstance;
}

void TimerBox_setValue(TimerBox * instance, char * time) {
    lv_label_set_text(instance->timerLabel, time);
}