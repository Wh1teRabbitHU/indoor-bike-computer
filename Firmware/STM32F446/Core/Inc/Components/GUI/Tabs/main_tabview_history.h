#ifndef __MAIN_TABVIEW_HISTORY_H_
#define __MAIN_TABVIEW_HISTORY_H_

#include "data.h"
#include "macros.h"
#include "run_list.h"
#include "state-handler.h"
#include "stdio.h"

typedef struct MainTabviewHistory_Config {
    lv_obj_t * tab;
} MainTabviewHistory_Config;

void MainTabviewHistory_init(MainTabviewHistory_Config * config);
void MainTabviewHistory_stepIn(void);
void MainTabviewHistory_execute(void);
uint8_t MainTabviewHistory_stepOut(void);
void MainTabviewHistory_handlePrev(void);
void MainTabviewHistory_handleNext(void);
void MainTabviewHistory_update(void);

#endif