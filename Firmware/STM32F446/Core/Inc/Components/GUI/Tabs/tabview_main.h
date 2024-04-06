#ifndef __TABVIEW_MAIN___H_
#define __TABVIEW_MAIN___H_

#include "app-state.h"
#include "lvgl.h"
#include "macros.h"
#include "tabview_main_tab_live.h"

#define GUI_TABVIEW_TAB_COUNT 3
#define GUI_TABVIEW_TAB_HEIGHT 40
#define GUI_TABVIEW_TABMAIN_BGCOLOR 0x000000
#define GUI_TABVIEW_TABHISTORY_BGCOLOR 0x000000
#define GUI_TABVIEW_TABSETTINGS_BGCOLOR 0x000000

typedef enum TabView_Main_TabLevel_t {
    TABVIEW_MAIN_TABLEVEL_TAB = 0,
    TABVIEW_MAIN_TABLEVEL_CONTENT = 1
} TabView_Main_TabLevel_t;

typedef enum TabView_Main_Tab_t {
    TABVIEW_MAIN_TAB_LIVE = 0,
    TABVIEW_MAIN_TAB_HISTORY = 1,
    TABVIEW_MAIN_TAB_SETTINGS = 2
} TabView_Main_Tab_t;

typedef struct TabView_Main {
    lv_obj_t* tabView;
    lv_obj_t* tabs[GUI_TABVIEW_TAB_COUNT];
    TabView_Main_Tab_t active;
} TabView_Main;

typedef struct TabView_Main_Config {
    lv_obj_t* screen;
} TabView_Main_Config;

typedef struct TabView_Main_State {
    char* infoMessage;
    char* errorMessage;
    uint32_t difficulty;
    uint32_t speed;
    uint32_t rpm;
    uint32_t bpm;
    uint8_t updateChart;
    uint8_t updateLevel;
    char* time;
} TabView_Main_State;

void TabView_Main_init(TabView_Main_Config* config);
void TabView_Main_prevTab();
void TabView_Main_nextTab();
void TabView_Main_update(void);

// Control handlers
void TabView_Main_handleSelect(void);
void TabView_Main_handleCancel(void);
void TabView_Main_handlePrev(void);
void TabView_Main_handleNext(void);

#endif