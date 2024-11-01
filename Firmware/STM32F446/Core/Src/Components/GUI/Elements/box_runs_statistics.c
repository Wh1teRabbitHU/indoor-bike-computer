#include "box_runs_statistics.h"

static char textBuffer[64] = {0};

BoxRunsStatistics BoxRunsStatistics_create(BoxRunsStatistics_Config* config) {
    BoxRunsStatistics runsStatistics = {0};

    lv_obj_t* box = lv_obj_create(config->screen);

    lv_obj_set_width(box, BOX_RUNS_STATISTICS_WIDTH);
    lv_obj_set_height(box, BOX_RUNS_STATISTICS_HEIGHT);
    lv_obj_set_pos(box, config->x, config->y);
    lv_obj_set_style_pad_all(box, BOX_RUNS_STATISTICS_MARGIN, LV_PART_MAIN);
    lv_obj_remove_flag(box, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(box, lv_color_hex(0xBCC7FF), LV_PART_MAIN);

    lv_obj_t* runsLabel = lv_label_create(box);

    lv_obj_set_style_text_color(runsLabel, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_align(runsLabel, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_set_width(runsLabel, BOX_RUNS_STATISTICS_WIDTH - 8);
    lv_obj_set_height(runsLabel, BOX_RUNS_STATISTICS_LABEL_HEIGHT);
    lv_obj_set_style_text_align(runsLabel, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);

    lv_obj_t* distanceSumLabel = lv_label_create(box);

    lv_obj_set_style_text_color(distanceSumLabel, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_align(distanceSumLabel, LV_ALIGN_TOP_LEFT, 0, BOX_RUNS_STATISTICS_LABEL_HEIGHT);
    lv_obj_set_width(distanceSumLabel, BOX_RUNS_STATISTICS_WIDTH - 8);
    lv_obj_set_height(runsLabel, BOX_RUNS_STATISTICS_LABEL_HEIGHT);
    lv_obj_set_style_text_align(distanceSumLabel, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);

    lv_obj_t* sessionsLengthLabel = lv_label_create(box);

    lv_obj_set_style_text_color(sessionsLengthLabel, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_align(sessionsLengthLabel, LV_ALIGN_TOP_LEFT, 0, BOX_RUNS_STATISTICS_LABEL_HEIGHT * 2);
    lv_obj_set_width(sessionsLengthLabel, BOX_RUNS_STATISTICS_WIDTH - 8);
    lv_obj_set_height(runsLabel, BOX_RUNS_STATISTICS_LABEL_HEIGHT);
    lv_obj_set_style_text_align(sessionsLengthLabel, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);

    runsStatistics.box = box;
    runsStatistics.runsLabel = runsLabel;
    runsStatistics.sessionsLengthLabel = sessionsLengthLabel;
    runsStatistics.distanceSumLabel = distanceSumLabel;

    return runsStatistics;
}

void BoxRunsStatistics_update(BoxRunsStatistics* instance, Data_Statistics* run) {
    sprintf(textBuffer, "Runs:  %lu", run->runs);
    lv_label_set_text(instance->runsLabel, textBuffer);

    uint32_t distanceKm = run->distanceSum / 1000;
    uint16_t distanceM = (run->distanceSum % 1000) / 10;

    sprintf(textBuffer, "Dist.: %lu,%02dkm", distanceKm, distanceM);
    lv_label_set_text(instance->distanceSumLabel, textBuffer);

    uint8_t minutes = 0;
    uint16_t hours = 0;

    minutes = (run->sessionsLength / 60) % 60;
    hours = (run->sessionsLength / 60 / 60) % 60;

    sprintf(textBuffer, "Time:  %dh %dm", hours, minutes);
    lv_label_set_text(instance->sessionsLengthLabel, textBuffer);
}