#include "box_measurement.h"

BoxMeasurement BoxMeasurement_create(BoxMeasurement_Config* config) {
    BoxMeasurement boxInstance = {};

    lv_obj_t* box = lv_obj_create(config->screen);

    lv_obj_align(box, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_set_width(box, 145);
    lv_obj_set_height(box, 100);
    lv_obj_set_pos(box, config->x, config->y);
    lv_obj_set_style_pad_all(box, 5, LV_PART_MAIN);
    lv_obj_remove_flag(box, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(box, lv_color_hex(config->bgColor), LV_PART_MAIN);

    lv_obj_t* titleLabel = lv_label_create(box);

    lv_obj_set_style_text_color(titleLabel, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_align(titleLabel, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_width(titleLabel, 135);
    lv_obj_set_style_text_align(titleLabel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_long_mode(titleLabel, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(titleLabel, config->title);

    lv_obj_t* avgLabel = lv_label_create(box);

    lv_obj_set_style_text_color(avgLabel, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_align(avgLabel, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_bottom(avgLabel, 10, LV_PART_MAIN);
    lv_obj_set_width(avgLabel, 68);
    lv_obj_set_style_text_align(avgLabel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_text(avgLabel, "Avg");

    lv_obj_t* avgValueLabel = lv_label_create(box);

    lv_obj_set_style_text_color(avgValueLabel, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_align(avgValueLabel, LV_ALIGN_BOTTOM_LEFT, 0, 0);
    lv_obj_set_width(avgValueLabel, 68);
    lv_obj_set_style_text_align(avgValueLabel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);

    lv_obj_t* curLabel = lv_label_create(box);

    lv_obj_set_style_text_color(curLabel, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_align(curLabel, LV_ALIGN_RIGHT_MID, 0, 0);
    lv_obj_set_style_pad_bottom(curLabel, 10, LV_PART_MAIN);
    lv_obj_set_width(curLabel, 68);
    lv_obj_set_style_text_align(curLabel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_text(curLabel, "Cur");

    lv_obj_t* curValueLabel = lv_label_create(box);

    lv_obj_set_style_text_color(curValueLabel, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_align(curValueLabel, LV_ALIGN_BOTTOM_RIGHT, 5, 0);
    lv_obj_set_width(curValueLabel, 68);
    lv_obj_set_style_text_align(curValueLabel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);

    static lv_style_t separatorStyle;
    lv_style_init(&separatorStyle);
    lv_style_set_line_width(&separatorStyle, 2);
    lv_style_set_line_color(&separatorStyle, lv_color_hex(0x000000));
    lv_style_set_line_rounded(&separatorStyle, true);

    static lv_point_precise_t line_points[] = {{2, 25}, {2, 85}};
    lv_obj_t* separator = lv_line_create(box);
    lv_line_set_points(separator, line_points, 2); /*Set the points*/
    lv_obj_add_style(separator, &separatorStyle, LV_PART_MAIN);
    lv_obj_center(separator);

    boxInstance.box = box;
    boxInstance.avgValueLabel = avgValueLabel;
    boxInstance.curValueLabel = curValueLabel;

    return boxInstance;
}

void BoxMeasurement_setValue(BoxMeasurement* instance, char* avgVal, char* curVal) {
    lv_label_set_text(instance->avgValueLabel, avgVal);
    lv_label_set_text(instance->curValueLabel, curVal);
}