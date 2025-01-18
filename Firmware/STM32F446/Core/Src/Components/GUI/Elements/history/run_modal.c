#include "run_modal.h"

Data_Run * selectedRun = NULL;

PRIVATE void RunModal_setupLabel(lv_obj_t * label, uint32_t offsetY) {
    lv_obj_set_style_text_color(label, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_align(label, LV_ALIGN_TOP_LEFT, 0, offsetY);
    lv_obj_set_width(label, RUN_MODAL_LABEL_WIDTH);
    lv_obj_set_height(label, RUN_MODAL_LABEL_HEIGHT);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);
}

PRIVATE void RunModal_setRunDetails(RunModal * instance, Data_Run * run) {
    char textBuffer[64] = {0};

    lv_label_set_text(instance->nameValueLabel, run->name);

    strncpy(textBuffer, run->created + 2, 17);
    lv_label_set_text(instance->createdValueLabel, textBuffer);

    uint8_t seconds = 0, minutes = 0, hours = 0;

    seconds = run->sessionLength % 60;
    minutes = (run->sessionLength / 60) % 60;
    hours   = (run->sessionLength / 60 / 60) % 60;

    sprintf(textBuffer, "%02d:%02d:%02d", hours, minutes, seconds);
    lv_label_set_text(instance->sessionLengthValueLabel, textBuffer);

    sprintf(textBuffer, "%lum", run->distance / 100);
    lv_label_set_text(instance->distanceValueLabel, textBuffer);

    sprintf(textBuffer, "%lu%%", DATA_AVG_CONVERT_VALUE(run->avgDifficulty));
    lv_label_set_text(instance->avgDifficultyValueLabel, textBuffer);

    uint8_t decimalSpeed  = DATA_AVG_CONVERT_VALUE(run->avgSpeed) / 100;
    uint8_t fractionSpeed = DATA_AVG_CONVERT_VALUE(run->avgSpeed) % 100;

    sprintf(textBuffer, "%d.%dkm/h", decimalSpeed, fractionSpeed);
    lv_label_set_text(instance->avgSpeedValueLabel, textBuffer);

    sprintf(textBuffer, "%lu", DATA_AVG_CONVERT_VALUE(run->avgRpm));
    lv_label_set_text(instance->avgRpmValueLabel, textBuffer);

    sprintf(textBuffer, "%lu", DATA_AVG_CONVERT_VALUE(run->avgBpm));
    lv_label_set_text(instance->avgBpmValueLabel, textBuffer);
}

RunModal RunModal_create(RunModal_Config * config) {
    RunModal runDetails = {0};

    lv_obj_t * box = lv_obj_create(config->screen);

    lv_obj_set_width(box, RUN_MODAL_WIDTH);
    lv_obj_set_height(box, RUN_MODAL_HEIGHT);
    lv_obj_set_pos(box, RUN_MODAL_PADDING, RUN_MODAL_PADDING);
    lv_obj_set_style_pad_all(box, 4, LV_PART_MAIN);
    lv_obj_remove_flag(box, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(box, lv_color_hex(RUN_MODAL_BG_COLOR), LV_PART_MAIN);
    lv_obj_add_flag(box, LV_OBJ_FLAG_HIDDEN);

    lv_obj_t * nameHeaderLabel          = lv_label_create(box);
    lv_obj_t * nameValueLabel           = lv_label_create(box);
    lv_obj_t * createdHeaderLabel       = lv_label_create(box);
    lv_obj_t * createdValueLabel        = lv_label_create(box);
    lv_obj_t * sessionLengthHeaderLabel = lv_label_create(box);
    lv_obj_t * sessionLengthValueLabel  = lv_label_create(box);
    lv_obj_t * distanceHeaderLabel      = lv_label_create(box);
    lv_obj_t * distanceValueLabel       = lv_label_create(box);
    lv_obj_t * avgDifficultyHeaderLabel = lv_label_create(box);
    lv_obj_t * avgDifficultyValueLabel  = lv_label_create(box);
    lv_obj_t * avgSpeedHeaderLabel      = lv_label_create(box);
    lv_obj_t * avgSpeedValueLabel       = lv_label_create(box);
    lv_obj_t * avgRpmHeaderLabel        = lv_label_create(box);
    lv_obj_t * avgRpmValueLabel         = lv_label_create(box);
    lv_obj_t * avgBpmHeaderLabel        = lv_label_create(box);
    lv_obj_t * avgBpmValueLabel         = lv_label_create(box);
    lv_obj_t * closeButton              = lv_button_create(box);
    lv_obj_t * deleteButton             = lv_button_create(box);

    lv_label_set_text(nameHeaderLabel, "Run name:");
    lv_label_set_text(createdHeaderLabel, "Created at:");
    lv_label_set_text(sessionLengthHeaderLabel, "Session length:");
    lv_label_set_text(distanceHeaderLabel, "Distance:");
    lv_label_set_text(avgDifficultyHeaderLabel, "Average diff.:");
    lv_label_set_text(avgSpeedHeaderLabel, "Average speed:");
    lv_label_set_text(avgRpmHeaderLabel, "Average RPM:");
    lv_label_set_text(avgBpmHeaderLabel, "Average BPM:");

    uint8_t labelCount = 0, groupCount = 0;
    uint32_t labelHeight  = RUN_MODAL_LABEL_HEIGHT;
    uint32_t labelPadding = RUN_MODAL_LABEL_GROUP_PADDING;

    RunModal_setupLabel(nameHeaderLabel, labelCount++);
    RunModal_setupLabel(nameValueLabel, (labelHeight * labelCount++) + (labelPadding * groupCount++));

    RunModal_setupLabel(createdHeaderLabel, (labelHeight * labelCount++) + (labelPadding * groupCount));
    RunModal_setupLabel(createdValueLabel, (labelHeight * labelCount++) + (labelPadding * groupCount++));

    RunModal_setupLabel(sessionLengthHeaderLabel, (labelHeight * labelCount++) + (labelPadding * groupCount));
    RunModal_setupLabel(sessionLengthValueLabel, (labelHeight * labelCount++) + (labelPadding * groupCount++));

    RunModal_setupLabel(distanceHeaderLabel, (labelHeight * labelCount++) + (labelPadding * groupCount));
    RunModal_setupLabel(distanceValueLabel, (labelHeight * labelCount++) + (labelPadding * groupCount++));

    RunModal_setupLabel(avgDifficultyHeaderLabel, (labelHeight * labelCount++) + (labelPadding * groupCount));
    RunModal_setupLabel(avgDifficultyValueLabel, (labelHeight * labelCount++) + (labelPadding * groupCount++));

    RunModal_setupLabel(avgSpeedHeaderLabel, (labelHeight * labelCount++) + (labelPadding * groupCount));
    RunModal_setupLabel(avgSpeedValueLabel, (labelHeight * labelCount++) + (labelPadding * groupCount++));

    RunModal_setupLabel(avgRpmHeaderLabel, (labelHeight * labelCount++) + (labelPadding * groupCount));
    RunModal_setupLabel(avgRpmValueLabel, (labelHeight * labelCount++) + (labelPadding * groupCount++));

    RunModal_setupLabel(avgBpmHeaderLabel, (labelHeight * labelCount++) + (labelPadding * groupCount));
    RunModal_setupLabel(avgBpmValueLabel, (labelHeight * labelCount++) + (labelPadding * groupCount++));

    lv_obj_align(closeButton, LV_ALIGN_BOTTOM_LEFT, 0, 0);
    lv_obj_set_width(closeButton, RUN_MODAL_BUTTON_WIDTH);
    lv_obj_set_height(closeButton, RUN_MODAL_BUTTON_HEIGHT);
    lv_obj_set_style_bg_color(closeButton, lv_color_hex(0xAAAAAA), LV_PART_MAIN);
    lv_obj_set_style_border_color(closeButton, lv_color_hex(0x777777), LV_PART_MAIN);
    lv_obj_set_style_border_width(closeButton, 0, LV_PART_MAIN);
    lv_obj_t * closeButtonLabel = lv_label_create(closeButton);
    lv_label_set_text(closeButtonLabel, "Close");
    lv_obj_center(closeButtonLabel);

    lv_obj_align(deleteButton, LV_ALIGN_BOTTOM_RIGHT, 0, 0);
    lv_obj_set_width(deleteButton, RUN_MODAL_BUTTON_WIDTH);
    lv_obj_set_height(deleteButton, RUN_MODAL_BUTTON_HEIGHT);
    lv_obj_set_style_bg_color(deleteButton, lv_color_hex(0xFF0000), LV_PART_MAIN);
    lv_obj_set_style_border_color(deleteButton, lv_color_hex(0xAA3333), LV_PART_MAIN);
    lv_obj_set_style_border_width(deleteButton, 0, LV_PART_MAIN);
    lv_obj_t * deleteButtonLabel = lv_label_create(deleteButton);
    lv_label_set_text(deleteButtonLabel, "Delete");
    lv_obj_center(deleteButtonLabel);

    runDetails.box                      = box;
    runDetails.nameHeaderLabel          = nameHeaderLabel;
    runDetails.nameValueLabel           = nameValueLabel;
    runDetails.createdHeaderLabel       = createdHeaderLabel;
    runDetails.createdValueLabel        = createdValueLabel;
    runDetails.sessionLengthHeaderLabel = sessionLengthHeaderLabel;
    runDetails.sessionLengthValueLabel  = sessionLengthValueLabel;
    runDetails.distanceHeaderLabel      = distanceHeaderLabel;
    runDetails.distanceValueLabel       = distanceValueLabel;
    runDetails.avgDifficultyHeaderLabel = avgDifficultyHeaderLabel;
    runDetails.avgDifficultyValueLabel  = avgDifficultyValueLabel;
    runDetails.avgSpeedHeaderLabel      = avgSpeedHeaderLabel;
    runDetails.avgSpeedValueLabel       = avgSpeedValueLabel;
    runDetails.avgRpmHeaderLabel        = avgRpmHeaderLabel;
    runDetails.avgRpmValueLabel         = avgRpmValueLabel;
    runDetails.avgBpmHeaderLabel        = avgBpmHeaderLabel;
    runDetails.avgBpmValueLabel         = avgBpmValueLabel;
    runDetails.closeButton              = closeButton;
    runDetails.deleteButton             = deleteButton;
    runDetails.selectedButton           = RUN_MODAL_CLOSE;
    runDetails.open                     = 0;
    runDetails.updated                  = 1;

    return runDetails;
}

void RunModal_open(RunModal * instance) {
    instance->open           = 1;
    instance->updated        = 0;
    instance->selectedButton = RUN_MODAL_CLOSE;
}

void RunModal_close(RunModal * instance) {
    instance->open    = 0;
    instance->updated = 0;
}

void RunModal_selectPrev(RunModal * instance) {
    if (instance->open) {
        uint8_t closeSelected = instance->selectedButton == RUN_MODAL_CLOSE;

        instance->selectedButton = closeSelected ? RUN_MODAL_DELETE : RUN_MODAL_CLOSE;
        instance->updated        = 0;
    }
}

void RunModal_selectNext(RunModal * instance) {
    if (instance->open) {
        uint8_t closeSelected = instance->selectedButton == RUN_MODAL_CLOSE;

        instance->selectedButton = closeSelected ? RUN_MODAL_DELETE : RUN_MODAL_CLOSE;
        instance->updated        = 0;
    }
}

uint8_t RunModal_execute(RunModal * instance) {
    switch (instance->selectedButton) {
    case RUN_MODAL_DELETE:
        Data_removeRunFromStatistics(selectedRun);
        Data_deleteRun(selectedRun);
        RunModal_close(instance);

        return 1;
    case RUN_MODAL_CLOSE:
    default:
        RunModal_close(instance);

        return 0;
    }
}

uint8_t RunModal_stepOut(RunModal * instance) {
    RunModal_close(instance);

    return 0;
}

void RunModal_update(RunModal * instance, Data_Run * run) {
    if (instance->updated) {
        return;
    }

    selectedRun = run;

    switch (instance->selectedButton) {
    case RUN_MODAL_CLOSE:
        lv_obj_set_style_shadow_width(instance->closeButton, 0, LV_PART_MAIN);
        lv_obj_set_style_shadow_width(instance->deleteButton, 3, LV_PART_MAIN);
        lv_obj_set_style_border_width(instance->closeButton, 3, LV_PART_MAIN);
        lv_obj_set_style_border_width(instance->deleteButton, 0, LV_PART_MAIN);
        break;
    case RUN_MODAL_DELETE:
        lv_obj_set_style_shadow_width(instance->closeButton, 3, LV_PART_MAIN);
        lv_obj_set_style_shadow_width(instance->deleteButton, 0, LV_PART_MAIN);
        lv_obj_set_style_border_width(instance->closeButton, 0, LV_PART_MAIN);
        lv_obj_set_style_border_width(instance->deleteButton, 3, LV_PART_MAIN);
        break;
    }

    if (instance->open) {
        RunModal_setRunDetails(instance, run);

        lv_obj_clear_flag(instance->box, LV_OBJ_FLAG_HIDDEN);
    } else {
        lv_obj_add_flag(instance->box, LV_OBJ_FLAG_HIDDEN);
    }

    instance->updated = 1;
}