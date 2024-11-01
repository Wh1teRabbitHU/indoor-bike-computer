#ifndef __BOX_RUNS_STATISTICS_H_
#define __BOX_RUNS_STATISTICS_H_

#include "data.h"
#include "lvgl.h"

#define BOX_RUNS_STATISTICS_LABEL_HEIGHT 24
#define BOX_RUNS_STATISTICS_MARGIN 4
#define BOX_RUNS_STATISTICS_WIDTH 310
#define BOX_RUNS_STATISTICS_HEIGHT ((BOX_RUNS_STATISTICS_LABEL_HEIGHT * 3) + (BOX_RUNS_STATISTICS_MARGIN * 2))

typedef struct BoxRunsStatistics {
    lv_obj_t* box;
    lv_obj_t* runsLabel;
    lv_obj_t* sessionsLengthLabel;
    lv_obj_t* distanceSumLabel;
} BoxRunsStatistics;

typedef struct BoxRunsStatistics_Config {
    lv_obj_t* screen;
    int32_t x;
    int32_t y;
} BoxRunsStatistics_Config;

BoxRunsStatistics BoxRunsStatistics_create(BoxRunsStatistics_Config* config);
void BoxRunsStatistics_update(BoxRunsStatistics* instance, Data_Statistics* run);

#endif