#ifndef __RUN_STATISTICS_H_
#define __RUN_STATISTICS_H_

#include "data.h"
#include "lvgl.h"

#define RUN_STATISTICS_LABEL_HEIGHT 24
#define RUN_STATISTICS_MARGIN       4
#define RUN_STATISTICS_WIDTH        310
#define RUN_STATISTICS_HEIGHT       ((RUN_STATISTICS_LABEL_HEIGHT * 3) + (RUN_STATISTICS_MARGIN * 2))

typedef struct RunStatistics {
    lv_obj_t * box;
    lv_obj_t * runsLabel;
    lv_obj_t * sessionsLengthLabel;
    lv_obj_t * distanceSumLabel;
} RunStatistics;

typedef struct RunStatistics_Config {
    lv_obj_t * screen;
    int32_t x;
    int32_t y;
} RunStatistics_Config;

RunStatistics RunStatistics_create(RunStatistics_Config * config);
void RunStatistics_update(RunStatistics * instance, Data_Statistics * run);

#endif