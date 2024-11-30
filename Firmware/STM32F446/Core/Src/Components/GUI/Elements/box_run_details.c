#include "box_run_details.h"

BoxRunDetails BoxRunDetails_create(BoxRunDetails_Config * config) {
    BoxRunDetails runDetails = {0};

    lv_obj_t * box = lv_obj_create(config->screen);

    lv_obj_set_width(box, BOX_RUN_DETAILS_WIDTH);
    lv_obj_set_height(box, BOX_RUN_DETAILS_HEIGHT);
    lv_obj_set_pos(box, config->x, config->y);
    lv_obj_set_style_pad_all(box, 4, LV_PART_MAIN);
    lv_obj_remove_flag(box, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(box, lv_color_hex(BOX_RUN_DETAILS_DEFAULT_BG_COLOR), LV_PART_MAIN);

    lv_obj_t * nameLabel = lv_label_create(box);

    lv_obj_set_style_text_color(nameLabel, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_align(nameLabel, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_set_width(nameLabel, BOX_RUN_DETAILS_WIDTH);
    lv_obj_set_style_text_align(nameLabel, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);

    lv_obj_t * createdLabel = lv_label_create(box);

    lv_obj_set_style_text_color(createdLabel, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_align(createdLabel, LV_ALIGN_TOP_LEFT, 0, 24);
    lv_obj_set_width(createdLabel, BOX_RUN_DETAILS_WIDTH);
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

void BoxRunDetails_changeSelection(BoxRunDetails * instance, uint8_t selected) {
    lv_color_t bgColor =
        selected ? lv_color_hex(BOX_RUN_DETAILS_SELECTED_BG_COLOR) : lv_color_hex(BOX_RUN_DETAILS_DEFAULT_BG_COLOR);
    lv_color_t borderColor = selected ? lv_color_hex(BOX_RUN_DETAILS_SELECTED_BORDER_COLOR)
                                      : lv_color_hex(BOX_RUN_DETAILS_DEFAULT_BORDER_COLOR);

    lv_obj_set_style_bg_color(instance->box, bgColor, LV_PART_MAIN);
    lv_obj_set_style_border_color(instance->box, borderColor, LV_PART_MAIN);
}

void BoxRunDetails_setRun(BoxRunDetails * instance, Data_Run * run) {
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

void BoxRunDetails_clearRun(BoxRunDetails * instance) {
    lv_obj_add_flag(instance->box, LV_OBJ_FLAG_HIDDEN);
}

void BoxRunDetails_show(BoxRunDetails * instance) {
    lv_obj_remove_flag(instance->box, LV_OBJ_FLAG_HIDDEN);
}

void BoxRunDetails_hide(BoxRunDetails * instance) {
    lv_obj_add_flag(instance->box, LV_OBJ_FLAG_HIDDEN);
}