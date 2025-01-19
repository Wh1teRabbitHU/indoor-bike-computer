#ifndef __MAIN_TABVIEW___H_
#define __MAIN_TABVIEW___H_

#include "lvgl.h"
#include "macros.h"
#include "main_tabview_history.h"
#include "main_tabview_live.h"
#include "state.h"

#define TABVIEW_TAB_COUNT           3
#define TABVIEW_TAB_HEIGHT          40
#define TABVIEW_TABMAIN_BGCOLOR     0x000000
#define TABVIEW_TABHISTORY_BGCOLOR  0x000000
#define TABVIEW_TABSETTINGS_BGCOLOR 0x000000

typedef enum MainTabview_TabLevel_t {
    MAIN_TABVIEW_TABLEVEL_TAB     = 0,
    MAIN_TABVIEW_TABLEVEL_CONTENT = 1
} MainTabview_TabLevel_t;

typedef enum MainTabview_Tab_t {
    MAIN_TABVIEW_TAB_LIVE     = 0,
    MAIN_TABVIEW_TAB_HISTORY  = 1,
    MAIN_TABVIEW_TAB_SETTINGS = 2
} MainTabview_Tab_t;

typedef struct MainTabview {
    lv_obj_t * tabView;
    lv_obj_t * tabs[TABVIEW_TAB_COUNT];
    MainTabview_Tab_t active;
} MainTabview;

typedef struct MainTabview_Config {
    lv_obj_t * screen;
} MainTabview_Config;

void MainTabview_init(MainTabview_Config * config);
void MainTabview_prevTab();
void MainTabview_nextTab();
void MainTabview_update(void);

// Control handlers
void MainTabview_handleSelect(void);
void MainTabview_handleCancel(void);
void MainTabview_handlePrev(void);
void MainTabview_handleNext(void);

#endif