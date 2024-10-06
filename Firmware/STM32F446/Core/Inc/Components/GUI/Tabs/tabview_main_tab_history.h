#ifndef __TABVIEW_MAIN_TAB_HISTORY_H_
#define __TABVIEW_MAIN_TAB_HISTORY_H_

#include "data.h"
#include "list_run_details.h"
#include "macros.h"
#include "state-handler.h"
#include "stdio.h"

typedef struct TabView_Main_Tab_History_Config {
    lv_obj_t* tab;
} TabView_Main_Tab_History_Config;

void TabView_Main_Tab_History_init(TabView_Main_Tab_History_Config* config);
void TabView_Main_Tab_History_stepIn(void);
void TabView_Main_Tab_History_stepOut(void);
void TabView_Main_Tab_History_execute(void);
void TabView_Main_Tab_History_handlePrev(void);
void TabView_Main_Tab_History_handleNext(void);

#endif