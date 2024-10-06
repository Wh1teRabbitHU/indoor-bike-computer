#ifndef __LIST_RUN_DETAILS_H_
#define __LIST_RUN_DETAILS_H_

#include "box_run_details.h"
#include "data.h"
#include "label_loading.h"
#include "lvgl.h"

#define LIST_RUN_DETAILS_MAX_RUN_COUNT DATA_RUNS_PAGE_SIZE

typedef struct ListRunDetails {
    LabelLoading loadingLabel;
    BoxRunDetails boxes[LIST_RUN_DETAILS_MAX_RUN_COUNT];
} ListRunDetails;

typedef struct ListRunDetails_Config {
    lv_obj_t* screen;
} ListRunDetails_Config;

ListRunDetails ListRunDetails_create(ListRunDetails_Config* config);
void ListRunDetails_loadRuns(ListRunDetails* instance);
void ListRunDetails_clearRuns(ListRunDetails* instance);
void ListRunDetails_selectPrev(ListRunDetails* instance);
void ListRunDetails_selectNext(ListRunDetails* instance);

#endif