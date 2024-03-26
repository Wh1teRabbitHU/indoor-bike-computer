#include "gui_screen_main.h"

static char textBuffer[32];

static uint8_t initialised = 0;
static lv_obj_t* mainScreen = NULL;

static GUI_TabMain mainTab;
static GUI_BoxMeasurement difficultyBox;
static GUI_BoxMeasurement speedBox;
static GUI_BoxMeasurement revolutionBox;
static GUI_BoxMeasurement heartRateBox;
static GUI_ChartMeasurement measurementChart;
static GUI_LabelTimer timerLabel;

static GUI_ScreenMain_State state = {
    .infoMessage = NULL, .errorMessage = NULL, .difficulty = 0, .speed = 0, .rpm = 0, .bpm = 0};

void GUI_MainScreen_initElements(void) {
    GUI_TabMain_Config mainTabConfig = {.screen = mainScreen, .height = 40};

    mainTab = GUI_TabMain_create(&mainTabConfig);

    lv_obj_t* mainTabObj = mainTab.tabs[GUI_TAB_MAIN];

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

void GUI_ScreenMain_init(void) {
    if (mainScreen != NULL) {
        return;
    }

    mainScreen = lv_obj_create(NULL);

    lv_screen_load(mainScreen);
    lv_obj_set_style_bg_color(mainScreen, lv_color_hex(GUI_MAINSCREEN_BGCOLOR), LV_PART_MAIN);

    GUI_MainScreen_initElements();

    initialised = 1;
}

void GUI_displayDifficulty(uint32_t difficulty) {
    sprintf(textBuffer, "%ld\nmV", difficulty);

    GUI_BoxMeasurement_setValue(&difficultyBox, textBuffer, textBuffer);
}

void GUI_displaySpeed(uint32_t speed) {
    sprintf(textBuffer, "%ld\nkmh", speed);

    GUI_BoxMeasurement_setValue(&speedBox, textBuffer, textBuffer);
}

void GUI_displayRevolution(uint32_t rpm) {
    sprintf(textBuffer, "%ld\nrpm", rpm);

    GUI_BoxMeasurement_setValue(&revolutionBox, textBuffer, textBuffer);
}

void GUI_displayHeartRate(uint32_t bpm) {
    sprintf(textBuffer, "%ld\nbpm", bpm);

    GUI_BoxMeasurement_setValue(&heartRateBox, textBuffer, textBuffer);
}

void GUI_displayMeasurementChart() {
    if (state.updateChart) {
        state.updateChart = 0;

        // TODO: Replace with a proper implementation
        GUI_ChartMeasurement_setValue(&measurementChart, lv_rand(70, 90));
    }
}

void GUI_displayTimerLabel(char* time) { GUI_LabelTimer_setValue(&timerLabel, time); }

void GUI_displayActiveTab(GUI_TabMain_t activeTab) {
    if (mainTab.active == activeTab) {
        return;
    }

    GUI_TabMain_setActive(&mainTab, activeTab);
}

void GUI_ScreenMain_updateStates(void) {
    GUI_displayDifficulty(state.difficulty);
    GUI_displaySpeed(state.speed);
    GUI_displayRevolution(state.rpm);
    GUI_displayHeartRate(state.bpm);
    GUI_displayMeasurementChart();
    GUI_displayTimerLabel(state.time);
    GUI_displayActiveTab(state.activeTab);
}

GUI_ScreenMain_State* GUI_ScreenMain_getState(void) { return &state; }