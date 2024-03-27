#include "tabview_main_tab_live.h"

static GUI_BoxMeasurement difficultyBox;
static GUI_BoxMeasurement speedBox;
static GUI_BoxMeasurement revolutionBox;
static GUI_BoxMeasurement heartRateBox;
static GUI_ChartMeasurement measurementChart;
static GUI_LabelTimer timerLabel;

static char textBuffer[32] = {0};

void TabView_Main_Tab_Live_init(TabView_Main_Tab_Live_Config* config) {
    GUI_BoxMeasurement_Config difficultyBoxConfig = {
        .screen = config->tab, .title = "Difficulty", .x = 10, .y = 10, .bgColor = 0xBCC7FF};
    GUI_BoxMeasurement_Config speedBoxConfig = {
        .screen = config->tab, .title = "Speed", .x = 165, .y = 10, .bgColor = 0x77EEE6};
    GUI_BoxMeasurement_Config revolutionBoxConfig = {
        .screen = config->tab, .title = "Revolution", .x = 10, .y = 120, .bgColor = 0xBFFFA1};
    GUI_BoxMeasurement_Config heartRateBoxConfig = {
        .screen = config->tab, .title = "Heart Rate", .x = 165, .y = 120, .bgColor = 0xFFA490};
    GUI_ChartMeasurement_Config measurementChartConfig = {.screen = config->tab,
                                                          .title = "Revolution",
                                                          .x = 10,
                                                          .y = 230,
                                                          .mainColor = 0xE1F6FF,
                                                          .series1Color = 0x39B200};
    GUI_LabelTimer_Config timerLabelConfig = {
        .screen = config->tab, .name = "Timer: ", .x = 10, .y = 368, .bgColor = 0xC993FF};

    difficultyBox = GUI_BoxMeasurement_create(&difficultyBoxConfig);
    speedBox = GUI_BoxMeasurement_create(&speedBoxConfig);
    revolutionBox = GUI_BoxMeasurement_create(&revolutionBoxConfig);
    heartRateBox = GUI_BoxMeasurement_create(&heartRateBoxConfig);
    measurementChart = GUI_ChartMeasurement_create(&measurementChartConfig);
    timerLabel = GUI_LabelTimer_create(&timerLabelConfig);
}

void TabView_Main_Tab_Live_updateDifficulty(uint32_t difficulty) {
    sprintf(textBuffer, "%ld\nmV", difficulty);

    GUI_BoxMeasurement_setValue(&difficultyBox, textBuffer, textBuffer);
}

void TabView_Main_Tab_Live_updateSpeed(uint32_t speed) {
    sprintf(textBuffer, "%ld\nkmh", speed);

    GUI_BoxMeasurement_setValue(&speedBox, textBuffer, textBuffer);
}

void TabView_Main_Tab_Live_updateRevolution(uint32_t rpm) {
    sprintf(textBuffer, "%ld\nrpm", rpm);

    GUI_BoxMeasurement_setValue(&revolutionBox, textBuffer, textBuffer);
}

void TabView_Main_Tab_Live_updateHeartRate(uint32_t bpm) {
    sprintf(textBuffer, "%ld\nbpm", bpm);

    GUI_BoxMeasurement_setValue(&heartRateBox, textBuffer, textBuffer);
}

void TabView_Main_Tab_Live_updateChart(uint8_t updateChart) {
    if (!updateChart) {
        return;
    }

    // TODO: Replace with a proper implementation
    GUI_ChartMeasurement_setValue(&measurementChart, lv_rand(70, 90));
}

void TabView_Main_Tab_Live_updateTimer(char* time) { GUI_LabelTimer_setValue(&timerLabel, time); }
