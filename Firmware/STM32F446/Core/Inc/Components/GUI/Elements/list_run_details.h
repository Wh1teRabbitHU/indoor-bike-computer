#ifndef __LIST_RUN_DETAILS_H_
#define __LIST_RUN_DETAILS_H_

#include "box_run_details.h"
#include "box_runs_statistics.h"
#include "data.h"
#include "label_loading.h"
#include "label_page_header.h"
#include "lvgl.h"
#include "macros.h"
#include "modal_run_details.h"

#define LIST_RUN_DETAILS_BOX_COUNT DATA_RUNS_PAGE_SIZE

typedef struct ListRunDetails {
    LabelLoading loadingLabel;
    LabelPageHeader pageHeaderLabel;
    BoxRunsStatistics statistics;
    BoxRunDetails boxes[LIST_RUN_DETAILS_BOX_COUNT];
    ModalRunDetails modal;
} ListRunDetails;

typedef struct ListRunDetails_Config {
    lv_obj_t * screen;
} ListRunDetails_Config;

ListRunDetails ListRunDetails_create(ListRunDetails_Config * config);

void ListRunDetails_init(ListRunDetails * instance);
void ListRunDetails_triggerLoadRuns(ListRunDetails * instance);
void ListRunDetails_selectPrev(ListRunDetails * instance);
void ListRunDetails_selectNext(ListRunDetails * instance);
void ListRunDetails_execute(ListRunDetails * instance);
uint8_t ListRunDetails_stepOut(ListRunDetails * instance);
void ListRunDetails_update(ListRunDetails * instance);

#endif