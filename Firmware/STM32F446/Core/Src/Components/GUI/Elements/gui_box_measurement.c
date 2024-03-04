#include "gui_box_measurement.h"

GUI_BoxMeasurement_t GUI_BoxMeasurement_create(lv_obj_t* screen, int32_t x, int32_t y) {
    GUI_BoxMeasurement_t boxInstance = {};

    lv_obj_t* box = lv_obj_create(screen);

    lv_obj_align(box, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_set_width(box, 145);
    lv_obj_set_height(box, 100);
    lv_obj_set_pos(box, x, y);

    lv_obj_set_style_bg_color(box, lv_color_hex(0xFF0000), LV_PART_MAIN);

    lv_obj_t* valueLabel = lv_label_create(box);

    lv_obj_set_style_text_color(valueLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_align(valueLabel, LV_ALIGN_BOTTOM_MID, 0, 0);

    boxInstance.box = box;
    boxInstance.valueLabel = valueLabel;

    return boxInstance;
}

void GUI_BoxMeasurement_setValue(GUI_BoxMeasurement_t* instance, char* val) {
    lv_label_set_text(instance->valueLabel, val);
}