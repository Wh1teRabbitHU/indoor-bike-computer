#ifndef __RUN_LIST_H_
#define __RUN_LIST_H_

#include "data.h"
#include "loading_label.h"
#include "lvgl.h"
#include "macros.h"
#include "page_header.h"
#include "run_list_item.h"
#include "run_modal.h"
#include "run_statistics.h"

#define RUN_LIST_ITEM_COUNT DATA_RUNS_PAGE_SIZE

typedef struct RunList {
    LoadingLabel loadingLabel;
    PageHeader pageHeader;
    RunStatistics statistics;
    RunListItem items[RUN_LIST_ITEM_COUNT];
    RunModal modal;
} RunList;

typedef struct RunList_Config {
    lv_obj_t * screen;
} RunList_Config;

RunList RunList_create(RunList_Config * config);

void RunList_init(RunList * instance);
void RunList_triggerLoadRuns(RunList * instance);
void RunList_selectPrev(RunList * instance);
void RunList_selectNext(RunList * instance);
void RunList_execute(RunList * instance);
uint8_t RunList_stepOut(RunList * instance);
void RunList_update(RunList * instance);

#endif