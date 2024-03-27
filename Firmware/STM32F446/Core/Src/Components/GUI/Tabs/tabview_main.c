#include "tabview_main.h"

static TabView_Main mainTabView;
static GUI_BoxMeasurement difficultyBox;
static GUI_BoxMeasurement speedBox;
static GUI_BoxMeasurement revolutionBox;
static GUI_BoxMeasurement heartRateBox;
static GUI_ChartMeasurement measurementChart;
static GUI_LabelTimer timerLabel;

static TabView_Main_Tab_t active = TABVIEW_MAIN_TAB_LIVE;

static char textBuffer[32] = {0};

TabView_Main TabView_Main_create(TabView_Main_Config* config);

void TabView_Main_init(TabView_Main_Config* config) {
    mainTabView = TabView_Main_create(config);

    lv_obj_t* mainTabObj = mainTabView.tabs[TABVIEW_MAIN_TAB_LIVE];

    // Elements in the main tab
    GUI_BoxMeasurement_Config difficultyBoxConfig = {
        .screen = mainTabObj, .title = "Difficulty", .x = 10, .y = 10, .bgColor = 0xBCC7FF};
    GUI_BoxMeasurement_Config speedBoxConfig = {
        .screen = mainTabObj, .title = "Speed", .x = 165, .y = 10, .bgColor = 0x77EEE6};
    GUI_BoxMeasurement_Config revolutionBoxConfig = {
        .screen = mainTabObj, .title = "Revolution", .x = 10, .y = 120, .bgColor = 0xBFFFA1};
    GUI_BoxMeasurement_Config heartRateBoxConfig = {
        .screen = mainTabObj, .title = "Heart Rate", .x = 165, .y = 120, .bgColor = 0xFFA490};
    GUI_ChartMeasurement_Config measurementChartConfig = {.screen = mainTabObj,
                                                          .title = "Revolution",
                                                          .x = 10,
                                                          .y = 230,
                                                          .mainColor = 0xE1F6FF,
                                                          .series1Color = 0x39B200};
    GUI_LabelTimer_Config timerLabelConfig = {
        .screen = mainTabObj, .name = "Timer: ", .x = 10, .y = 368, .bgColor = 0xC993FF};

    difficultyBox = GUI_BoxMeasurement_create(&difficultyBoxConfig);
    speedBox = GUI_BoxMeasurement_create(&speedBoxConfig);
    revolutionBox = GUI_BoxMeasurement_create(&revolutionBoxConfig);
    heartRateBox = GUI_BoxMeasurement_create(&heartRateBoxConfig);
    measurementChart = GUI_ChartMeasurement_create(&measurementChartConfig);
    timerLabel = GUI_LabelTimer_create(&timerLabelConfig);

    // Elements in the history tab

    // TODO

    // Elements in the settings tab

    // TODO
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

    TabView_Main_setActive(&tabInstance, active);

    return tabInstance;
}

void TabView_Main_setActive(TabView_Main* instance, TabView_Main_Tab_t tab) {
    instance->active = tab;

    lv_tabview_set_active(instance->tabView, instance->active, LV_ANIM_OFF);
}

void TabView_Main_prevTab(TabView_Main* instance) {
    uint32_t current = instance->active;

    if (current == 0) {
        current = GUI_TABVIEW_TABCOUNT - 1;
    } else {
        current--;
    }

    TabView_Main_setActive(instance, current);
}

void TabView_Main_nextTab(TabView_Main* instance) {
    uint32_t current = instance->active;

    if (current == (GUI_TABVIEW_TABCOUNT - 1)) {
        current = 0;
    } else {
        current++;
    }

    TabView_Main_setActive(instance, current);
}

void TabView_Main_displayDifficulty(uint32_t difficulty) {
    sprintf(textBuffer, "%ld\nmV", difficulty);

    GUI_BoxMeasurement_setValue(&difficultyBox, textBuffer, textBuffer);
}

void TabView_Main_displaySpeed(uint32_t speed) {
    sprintf(textBuffer, "%ld\nkmh", speed);

    GUI_BoxMeasurement_setValue(&speedBox, textBuffer, textBuffer);
}

void TabView_Main_displayRevolution(uint32_t rpm) {
    sprintf(textBuffer, "%ld\nrpm", rpm);

    GUI_BoxMeasurement_setValue(&revolutionBox, textBuffer, textBuffer);
}

void TabView_Main_displayHeartRate(uint32_t bpm) {
    sprintf(textBuffer, "%ld\nbpm", bpm);

    GUI_BoxMeasurement_setValue(&heartRateBox, textBuffer, textBuffer);
}

void TabView_Main_displayMeasurementChart(TabView_Main_State* state) {
    if (state->updateChart) {
        state->updateChart = 0;

        // TODO: Replace with a proper implementation
        GUI_ChartMeasurement_setValue(&measurementChart, lv_rand(70, 90));
    }
}

void TabView_Main_displayTimerLabel(char* time) { GUI_LabelTimer_setValue(&timerLabel, time); }

void TabView_Main_displayActiveTab(TabView_Main_Tab_t activeTab) {
    if (mainTabView.active == activeTab) {
        return;
    }

    TabView_Main_setActive(&mainTabView, activeTab);
}

void TabView_Main_updateStates(TabView_Main_State* state) {
    TabView_Main_displayActiveTab(state->activeTab);
    TabView_Main_displayDifficulty(state->difficulty);
    TabView_Main_displaySpeed(state->speed);
    TabView_Main_displayRevolution(state->rpm);
    TabView_Main_displayHeartRate(state->bpm);
    TabView_Main_displayMeasurementChart(state);
    TabView_Main_displayTimerLabel(state->time);
}