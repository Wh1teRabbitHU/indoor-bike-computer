#include "main_tabview.h"

static MainTabview mainTabView;
static MainTabview_Tab_t activeTab           = MAIN_TABVIEW_TAB_LIVE;
static MainTabview_TabLevel_t activeTabLevel = MAIN_TABVIEW_TABLEVEL_TAB;

// PRIVATE METHODS

PRIVATE void MainTabview_setActiveTab(MainTabview_Tab_t tab) {
    mainTabView.active = tab;

    lv_tabview_set_active(mainTabView.tabView, mainTabView.active, LV_ANIM_OFF);
}

PRIVATE void MainTabview_updateTabLive() {
    State_Live * state = State_getLive();

    if (state->running) {
        Data_Run * run = &state->liveRun;

        MainTabviewLive_updateDifficulty(state->difficulty, run->avgDifficulty);
        MainTabviewLive_updateSpeed(state->speed, run->avgSpeed);
        MainTabviewLive_updateDistance(run->distance);
        MainTabviewLive_updateHeartRate(state->bpm, run->avgBpm);
        MainTabviewLive_updateChart(state->updateChart);
        MainTabviewLive_updateTimer(state->time);
    } else {
        MainTabviewLive_updateDifficulty(state->difficulty, 0);
        MainTabviewLive_updateSpeed(state->speed, 0);
        MainTabviewLive_updateDistance(0);
        MainTabviewLive_updateHeartRate(state->bpm, 0);
        MainTabviewLive_updateChart(0);
        MainTabviewLive_updateTimer(state->time);
    }

    MainTabviewLive_updateControl();

    state->updateChart = 0;
}

PRIVATE void MainTabview_updateTabHistory() {
    MainTabviewHistory_update();
}

PRIVATE MainTabview MainTabview_create(MainTabview_Config * config) {
    MainTabview tabInstance = {.tabs = {0}};

    lv_obj_t * tabView = lv_tabview_create(config->screen);

    lv_obj_set_style_bg_color(tabView, lv_color_hex(TABVIEW_TABMAIN_BGCOLOR), 0);
    lv_tabview_set_tab_bar_position(tabView, LV_DIR_BOTTOM);
    lv_tabview_set_tab_bar_size(tabView, TABVIEW_TAB_HEIGHT);

    lv_obj_t * tabMain     = lv_tabview_add_tab(tabView, "Live");
    lv_obj_t * tabHistory  = lv_tabview_add_tab(tabView, "Hist.");
    lv_obj_t * tabSettings = lv_tabview_add_tab(tabView, "Set.");

    lv_obj_set_style_pad_all(tabMain, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_color(tabMain, lv_color_hex(TABVIEW_TABMAIN_BGCOLOR), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(tabMain, LV_OPA_COVER, 0);

    lv_obj_set_style_pad_all(tabHistory, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_color(tabHistory, lv_color_hex(TABVIEW_TABHISTORY_BGCOLOR), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(tabHistory, LV_OPA_COVER, 0);

    lv_obj_set_style_pad_all(tabSettings, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_color(tabSettings, lv_color_hex(TABVIEW_TABSETTINGS_BGCOLOR), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(tabSettings, LV_OPA_COVER, 0);

    tabInstance.tabView = tabView;

    tabInstance.tabs[MAIN_TABVIEW_TAB_LIVE]     = tabMain;
    tabInstance.tabs[MAIN_TABVIEW_TAB_HISTORY]  = tabHistory;
    tabInstance.tabs[MAIN_TABVIEW_TAB_SETTINGS] = tabSettings;

    tabInstance.active = MAIN_TABVIEW_TAB_LIVE;

    return tabInstance;
}

PRIVATE void MainTabview_TabLevel_stepIn() {
    activeTabLevel = MAIN_TABVIEW_TABLEVEL_CONTENT;

    switch (activeTab) {
    case MAIN_TABVIEW_TAB_LIVE:
        MainTabviewLive_stepIn();
        break;
    case MAIN_TABVIEW_TAB_HISTORY:
        MainTabviewHistory_stepIn();
        break;
    case MAIN_TABVIEW_TAB_SETTINGS:
        // TODO
        break;
    }

    State_getGlobal()->updateLevel = 1;
}

PRIVATE void MainTabview_TabLevel_stepOut() {
    uint8_t triggerStepOut = 1;

    switch (activeTab) {
    case MAIN_TABVIEW_TAB_LIVE:
        MainTabviewLive_stepOut();
        break;
    case MAIN_TABVIEW_TAB_HISTORY:
        triggerStepOut = MainTabviewHistory_stepOut();
        break;
    case MAIN_TABVIEW_TAB_SETTINGS:
        // TODO
        break;
    }

    if (triggerStepOut) {
        activeTabLevel = MAIN_TABVIEW_TABLEVEL_TAB;
    }

    State_getGlobal()->updateLevel = 1;
}

PRIVATE void MainTabview_TabLevel_execute() {
    switch (activeTab) {
    case MAIN_TABVIEW_TAB_LIVE:
        MainTabviewLive_execute();
        break;
    case MAIN_TABVIEW_TAB_HISTORY:
        MainTabviewHistory_execute();
        break;
    case MAIN_TABVIEW_TAB_SETTINGS:
        // TODO
        break;
    }
}

PRIVATE void MainTabview_TabLevel_handlePrev() {
    switch (activeTab) {
    case MAIN_TABVIEW_TAB_LIVE:
        MainTabviewLive_handlePrev();
        break;
    case MAIN_TABVIEW_TAB_HISTORY:
        MainTabviewHistory_handlePrev();
        break;
    case MAIN_TABVIEW_TAB_SETTINGS:
        // TODO
        break;
    }
}

PRIVATE void MainTabview_TabLevel_handleNext() {
    switch (activeTab) {
    case MAIN_TABVIEW_TAB_LIVE:
        MainTabviewLive_handleNext();
        break;
    case MAIN_TABVIEW_TAB_HISTORY:
        MainTabviewHistory_handleNext();
        break;
    case MAIN_TABVIEW_TAB_SETTINGS:
        // TODO
        break;
    }
}

// PUBLIC METHODS

void MainTabview_init(MainTabview_Config * config) {
    mainTabView = MainTabview_create(config);

    MainTabview_setActiveTab(activeTab);

    lv_obj_t * tabLiveObj    = mainTabView.tabs[MAIN_TABVIEW_TAB_LIVE];
    lv_obj_t * tabHistoryObj = mainTabView.tabs[MAIN_TABVIEW_TAB_HISTORY];

    MainTabviewLive_Config tabLiveConfig       = {.tab = tabLiveObj};
    MainTabviewHistory_Config tabHistoryConfig = {.tab = tabHistoryObj};

    MainTabviewLive_init(&tabLiveConfig);
    MainTabviewHistory_init(&tabHistoryConfig);
}

void MainTabview_prevTab() {
    uint32_t current = mainTabView.active;

    if (current == 0) {
        current = TABVIEW_TAB_COUNT - 1;
    } else {
        current--;
    }

    activeTab = current;
}

void MainTabview_nextTab() {
    uint32_t current = mainTabView.active;

    if (current == (TABVIEW_TAB_COUNT - 1)) {
        current = 0;
    } else {
        current++;
    }

    activeTab = current;
}

void MainTabview_update() {
    if (mainTabView.active != activeTab) {
        MainTabview_setActiveTab(activeTab);
    }

    switch (activeTab) {
    case MAIN_TABVIEW_TAB_LIVE:
        MainTabview_updateTabLive();
        break;
    case MAIN_TABVIEW_TAB_HISTORY:
        MainTabview_updateTabHistory();
        break;
    case MAIN_TABVIEW_TAB_SETTINGS:
        // Do nothing
        break;
    }

    if (State_getGlobal()->updateLevel) {
        // Change the tab height based on the level
        int32_t tabViewHeight = activeTabLevel == MAIN_TABVIEW_TABLEVEL_TAB ? TABVIEW_TAB_HEIGHT : 0;

        lv_tabview_set_tab_bar_size(mainTabView.tabView, tabViewHeight);

        State_getGlobal()->updateLevel = 0;
    }
}

void MainTabview_handleSelect(void) {
    switch (activeTabLevel) {
    case MAIN_TABVIEW_TABLEVEL_TAB:
        MainTabview_TabLevel_stepIn();
        break;
    case MAIN_TABVIEW_TABLEVEL_CONTENT:
        MainTabview_TabLevel_execute();
        break;
    }
}

void MainTabview_handleCancel(void) {
    switch (activeTabLevel) {
    case MAIN_TABVIEW_TABLEVEL_TAB:
        // Do nothing
        break;
    case MAIN_TABVIEW_TABLEVEL_CONTENT:
        MainTabview_TabLevel_stepOut();
        break;
    }
}

void MainTabview_handlePrev(void) {
    switch (activeTabLevel) {
    case MAIN_TABVIEW_TABLEVEL_TAB:
        MainTabview_prevTab();
        break;
    case MAIN_TABVIEW_TABLEVEL_CONTENT:
        MainTabview_TabLevel_handlePrev();
        break;
    }
}

void MainTabview_handleNext(void) {
    switch (activeTabLevel) {
    case MAIN_TABVIEW_TABLEVEL_TAB:
        MainTabview_nextTab();
        break;
    case MAIN_TABVIEW_TABLEVEL_CONTENT:
        MainTabview_TabLevel_handleNext();
        break;
    }
}