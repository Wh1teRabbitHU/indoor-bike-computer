#ifndef __TABVIEW_MAIN___H_
#define __TABVIEW_MAIN___H_

#include "lvgl.h"
#include "tabview_main_tab_live.h"

#define GUI_TABVIEW_TABCOUNT 3
#define GUI_TABVIEW_TABMAIN_BGCOLOR 0x000000
#define GUI_TABVIEW_TABHISTORY_BGCOLOR 0x000000
#define GUI_TABVIEW_TABSETTINGS_BGCOLOR 0x000000

typedef enum TabView_Main_Tab_t {
    TABVIEW_MAIN_TAB_LIVE = 0,
    TABVIEW_MAIN_TAB_HISTORY = 1,
    TABVIEW_MAIN_TAB_SETTINGS = 2
} TabView_Main_Tab_t;

typedef struct TabView_Main {
    lv_obj_t* tabView;
    lv_obj_t* tabs[GUI_TABVIEW_TABCOUNT];
    TabView_Main_Tab_t active;
} TabView_Main;

typedef struct TabView_Main_Config {
    lv_obj_t* screen;
    int32_t height;
    uint32_t bgColor;
} TabView_Main_Config;

typedef struct TabView_Main_State {
    char* infoMessage;
    char* errorMessage;
    uint32_t difficulty;
    uint32_t speed;
    uint32_t rpm;
    uint32_t bpm;
    uint8_t updateChart;
    char* time;
    TabView_Main_Tab_t activeTab;
} TabView_Main_State;

void TabView_Main_init(TabView_Main_Config* config);
void TabView_Main_setActive(TabView_Main* instance, TabView_Main_Tab_t tab);
void TabView_Main_prevTab(TabView_Main* instance);
void TabView_Main_nextTab(TabView_Main* instance);
void TabView_Main_updateStates(TabView_Main_State* state);

#endif