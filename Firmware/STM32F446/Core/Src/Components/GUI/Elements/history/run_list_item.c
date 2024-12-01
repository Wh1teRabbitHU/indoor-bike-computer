#include "run_list_item.h"

RunListItem RunListItem_create(RunListItem_Config * config) {
    RunListItem runDetails = {0};

    lv_obj_t * box = lv_obj_create(config->screen);

    lv_obj_set_width(box, RUN_LIST_ITEM_WIDTH);
    lv_obj_set_height(box, RUN_LIST_ITEM_HEIGHT);
    lv_obj_set_pos(box, config->x, config->y);
    lv_obj_set_style_pad_all(box, 4, LV_PART_MAIN);
    lv_obj_remove_flag(box, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(box, lv_color_hex(RUN_LIST_ITEM_DEFAULT_BG_COLOR), LV_PART_MAIN);

    lv_obj_t * nameLabel = lv_label_create(box);

    lv_obj_set_style_text_color(nameLabel, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_align(nameLabel, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_set_width(nameLabel, RUN_LIST_ITEM_WIDTH);
    lv_obj_set_style_text_align(nameLabel, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);

    lv_obj_t * createdLabel = lv_label_create(box);

    lv_obj_set_style_text_color(createdLabel, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_align(createdLabel, LV_ALIGN_TOP_LEFT, 0, 24);
    lv_obj_set_width(createdLabel, RUN_LIST_ITEM_WIDTH);
    lv_obj_set_style_text_align(createdLabel, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);

    lv_obj_t * sessionLengthLabel = lv_label_create(box);

    lv_obj_set_style_text_color(sessionLengthLabel, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_align(sessionLengthLabel, LV_ALIGN_BOTTOM_LEFT, 0, 0);
    lv_obj_set_width(sessionLengthLabel, 140);
    lv_obj_set_style_text_align(sessionLengthLabel, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);

    lv_obj_t * distanceLabel = lv_label_create(box);

    lv_obj_set_style_text_color(distanceLabel, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_align(distanceLabel, LV_ALIGN_BOTTOM_RIGHT, 0, 0);
    lv_obj_set_width(distanceLabel, 140);
    lv_obj_set_style_text_align(distanceLabel, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN);

    runDetails.box                = box;
    runDetails.nameLabel          = nameLabel;
    runDetails.createdLabel       = createdLabel;
    runDetails.sessionLengthLabel = sessionLengthLabel;
    runDetails.distanceLabel      = distanceLabel;

    return runDetails;
}

void RunListItem_changeSelection(RunListItem * instance, uint8_t selected) {
    lv_color_t bgColor =
        selected ? lv_color_hex(RUN_LIST_ITEM_SELECTED_BG_COLOR) : lv_color_hex(RUN_LIST_ITEM_DEFAULT_BG_COLOR);
    lv_color_t borderColor = selected ? lv_color_hex(RUN_LIST_ITEM_SELECTED_BORDER_COLOR)
                                      : lv_color_hex(RUN_LIST_ITEM_DEFAULT_BORDER_COLOR);

    lv_obj_set_style_bg_color(instance->box, bgColor, LV_PART_MAIN);
    lv_obj_set_style_border_color(instance->box, borderColor, LV_PART_MAIN);
}

void RunListItem_setRun(RunListItem * instance, Data_Run * run) {
    char textBuffer[64] = {0};

    lv_label_set_text(instance->nameLabel, run->name);

    strncpy(textBuffer, run->created + 2, 17);
    lv_label_set_text(instance->createdLabel, textBuffer);

    uint8_t seconds = 0, minutes = 0, hours = 0;

    seconds = run->sessionLength % 60;
    minutes = (run->sessionLength / 60) % 60;
    hours   = (run->sessionLength / 60 / 60) % 60;

    sprintf(textBuffer, "%02d:%02d:%02d", hours, minutes, seconds);
    lv_label_set_text(instance->sessionLengthLabel, textBuffer);

    sprintf(textBuffer, "%lum", run->distance / 100);
    lv_label_set_text(instance->distanceLabel, textBuffer);

    lv_obj_clear_flag(instance->box, LV_OBJ_FLAG_HIDDEN);
}

void RunListItem_clearRun(RunListItem * instance) {
    lv_obj_add_flag(instance->box, LV_OBJ_FLAG_HIDDEN);
}

void RunListItem_show(RunListItem * instance) {
    lv_obj_remove_flag(instance->box, LV_OBJ_FLAG_HIDDEN);
}

void RunListItem_hide(RunListItem * instance) {
    lv_obj_add_flag(instance->box, LV_OBJ_FLAG_HIDDEN);
}