#include "page_header.h"

PageHeader PageHeader_create(PageHeader_Config * config) {
    PageHeader instance = {};

    lv_obj_t * box = lv_obj_create(config->screen);

    lv_obj_align(box, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_set_width(box, PAGE_HEADER_WIDTH);
    lv_obj_set_height(box, PAGE_HEADER_HEIGHT);
    lv_obj_set_pos(box, config->x, config->y);
    lv_obj_set_style_pad_all(box, 5, LV_PART_MAIN);
    lv_obj_remove_flag(box, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(box, lv_color_hex(PAGE_HEADER_BG_COLOR), LV_PART_MAIN);

    lv_obj_t * selectionLabel = lv_label_create(box);

    lv_obj_set_style_text_color(selectionLabel, lv_color_hex(PAGE_HEADER_TEXT_COLOR), LV_PART_MAIN);
    lv_obj_align(selectionLabel, LV_ALIGN_TOP_LEFT, 0, 5);
    lv_obj_set_style_pad_left(selectionLabel, 5, LV_PART_MAIN);
    lv_obj_set_width(selectionLabel, PAGE_HEADER_WIDTH / 2);
    lv_obj_set_style_text_align(selectionLabel, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);
    lv_label_set_text(selectionLabel, "0/0");

    lv_obj_t * rangeLabel = lv_label_create(box);

    lv_obj_set_style_text_color(rangeLabel, lv_color_hex(PAGE_HEADER_TEXT_COLOR), LV_PART_MAIN);
    lv_obj_align(rangeLabel, LV_ALIGN_TOP_RIGHT, 0, 5);
    lv_obj_set_style_pad_right(rangeLabel, 5, LV_PART_MAIN);
    lv_obj_set_width(rangeLabel, PAGE_HEADER_WIDTH / 2);
    lv_obj_set_style_text_align(rangeLabel, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN);
    lv_label_set_text(rangeLabel, "(0-0)");

    instance.box            = box;
    instance.selectionLabel = selectionLabel;
    instance.rangeLabel     = rangeLabel;

    return instance;
}

void PageHeader_update(PageHeader * instance) {
    char textBuffer[32] = {0};

    sprintf(textBuffer, "%lu/%lu", instance->selectedIndex, instance->elementCount);
    lv_label_set_text(instance->selectionLabel, textBuffer);

    sprintf(textBuffer, "(%lu-%lu)", instance->pageStart, instance->pageEnd);
    lv_label_set_text(instance->rangeLabel, textBuffer);
}