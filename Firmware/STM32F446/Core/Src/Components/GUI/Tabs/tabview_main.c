#include "tabview_main.h"

static TabView_Main mainTabView;
static TabView_Main_Tab_t activeTab = TABVIEW_MAIN_TAB_LIVE;
static TabView_Main_TabLevel_t activeTabLevel = TABVIEW_MAIN_TABLEVEL_TAB;
static TabView_Main_State state = {
    .infoMessage = NULL, .errorMessage = NULL, .difficulty = 0, .speed = 0, .rpm = 0, .bpm = 0};

void TabView_Main_setActiveTab(TabView_Main_Tab_t tab) {
    mainTabView.active = tab;

    lv_tabview_set_active(mainTabView.tabView, mainTabView.active, LV_ANIM_OFF);
}

TabView_Main TabView_Main_create(TabView_Main_Config* config) {
    TabView_Main tabInstance = {.tabs = {0}};

    lv_obj_t* tabView = lv_tabview_create(config->screen);

    lv_obj_set_style_bg_color(tabView, lv_color_hex(GUI_TABVIEW_TABMAIN_BGCOLOR), 0);
    lv_tabview_set_tab_bar_position(tabView, LV_DIR_BOTTOM);
    lv_tabview_set_tab_bar_size(tabView, config->height);

    lv_obj_t* tabMain = lv_tabview_add_tab(tabView, "Live");
    lv_obj_t* tabHistory = lv_tabview_add_tab(tabView, "Hist.");
    lv_obj_t* tabSettings = lv_tabview_add_tab(tabView, "Set.");

    lv_obj_set_style_pad_all(tabMain, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_color(tabMain, lv_color_hex(GUI_TABVIEW_TABMAIN_BGCOLOR), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(tabMain, LV_OPA_COVER, 0);

    lv_obj_set_style_pad_all(tabHistory, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_color(tabHistory, lv_color_hex(GUI_TABVIEW_TABHISTORY_BGCOLOR), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(tabHistory, LV_OPA_COVER, 0);

    lv_obj_set_style_pad_all(tabSettings, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_color(tabSettings, lv_color_hex(GUI_TABVIEW_TABSETTINGS_BGCOLOR), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(tabSettings, LV_OPA_COVER, 0);

    tabInstance.tabView = tabView;

    tabInstance.tabs[TABVIEW_MAIN_TAB_LIVE] = tabMain;
    tabInstance.tabs[TABVIEW_MAIN_TAB_HISTORY] = tabHistory;
    tabInstance.tabs[TABVIEW_MAIN_TAB_SETTINGS] = tabSettings;

    tabInstance.active = TABVIEW_MAIN_TAB_LIVE;

    return tabInstance;
}

void TabView_Main_prevTab() {
    uint32_t current = mainTabView.active;

    if (current == 0) {
        current = GUI_TABVIEW_TABCOUNT - 1;
    } else {
        current--;
    }

    activeTab = current;
}

void TabView_Main_nextTab() {
    uint32_t current = mainTabView.active;

    if (current == (GUI_TABVIEW_TABCOUNT - 1)) {
        current = 0;
    } else {
        current++;
    }

    activeTab = current;
}

void TabView_Main_updateTabLive(TabView_Main_State* state) {
    if (activeTab != TABVIEW_MAIN_TAB_LIVE) {
        return;
    }

    TabView_Main_Tab_Live_updateDifficulty(state->difficulty);
    TabView_Main_Tab_Live_updateSpeed(state->speed);
    TabView_Main_Tab_Live_updateRevolution(state->rpm);
    TabView_Main_Tab_Live_updateHeartRate(state->bpm);
    TabView_Main_Tab_Live_updateChart(state->updateChart);
    TabView_Main_Tab_Live_updateTimer(state->time);

    state->updateChart = 0;
}

void TabView_Main_init(TabView_Main_Config* config) {
    mainTabView = TabView_Main_create(config);

    TabView_Main_setActiveTab(activeTab);

    lv_obj_t* tabLiveObj = mainTabView.tabs[TABVIEW_MAIN_TAB_LIVE];

    TabView_Main_Tab_Live_Config tabLiveConfig = {.tab = tabLiveObj};
    TabView_Main_Tab_Live_init(&tabLiveConfig);
}

TabView_Main_State* TabView_Main_getState(void) { return &state; }

void TabView_Main_updateStates() {
    if (mainTabView.active != activeTab) {
        TabView_Main_setActiveTab(activeTab);
    }

    TabView_Main_updateTabLive(&state);
}

void TabView_Main_handleSelect(void) {
    switch (activeTabLevel) {
        case TABVIEW_MAIN_TABLEVEL_TAB:
            activeTabLevel = TABVIEW_MAIN_TABLEVEL_CONTENT;
            break;
        case TABVIEW_MAIN_TABLEVEL_CONTENT:
            // TODO
            break;
    }
}

void TabView_Main_handleCancel(void) {
    switch (activeTabLevel) {
        case TABVIEW_MAIN_TABLEVEL_TAB:
            // Do nothing
            break;
        case TABVIEW_MAIN_TABLEVEL_CONTENT:
            activeTabLevel = TABVIEW_MAIN_TABLEVEL_TAB;
            break;
    }
}

void TabView_Main_handlePrev(void) {
    switch (activeTabLevel) {
        case TABVIEW_MAIN_TABLEVEL_TAB:
            TabView_Main_prevTab();
            break;
        case TABVIEW_MAIN_TABLEVEL_CONTENT:
            // TODO
            break;
    }
}

void TabView_Main_handleNext(void) {
    switch (activeTabLevel) {
        case TABVIEW_MAIN_TABLEVEL_TAB:
            TabView_Main_nextTab();
            break;
        case TABVIEW_MAIN_TABLEVEL_CONTENT:
            // TODO
            break;
    }
}