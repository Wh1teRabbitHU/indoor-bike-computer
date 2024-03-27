#include "tabview_main_tab_live.h"

static BoxMeasurement difficultyBox;
static BoxMeasurement speedBox;
static BoxMeasurement revolutionBox;
static BoxMeasurement heartRateBox;
static ChartMeasurement measurementChart;
static LabelTimer timerLabel;

static char textBuffer[32] = {0};

void TabView_Main_Tab_Live_init(TabView_Main_Tab_Live_Config* config) {
    BoxMeasurement_Config difficultyBoxConfig = {
        .screen = config->tab, .title = "Difficulty", .x = 10, .y = 10, .bgColor = 0xBCC7FF};
    BoxMeasurement_Config speedBoxConfig = {
        .screen = config->tab, .title = "Speed", .x = 165, .y = 10, .bgColor = 0x77EEE6};
    BoxMeasurement_Config revolutionBoxConfig = {
        .screen = config->tab, .title = "Revolution", .x = 10, .y = 120, .bgColor = 0xBFFFA1};
    BoxMeasurement_Config heartRateBoxConfig = {
        .screen = config->tab, .title = "Heart Rate", .x = 165, .y = 120, .bgColor = 0xFFA490};
    ChartMeasurement_Config measurementChartConfig = {.screen = config->tab,
                                                      .title = "Revolution",
                                                      .x = 10,
                                                      .y = 230,
                                                      .mainColor = 0xE1F6FF,
                                                      .series1Color = 0x39B200};
    LabelTimer_Config timerLabelConfig = {
        .screen = config->tab, .name = "Timer: ", .x = 10, .y = 368, .bgColor = 0xC993FF};

    difficultyBox = BoxMeasurement_create(&difficultyBoxConfig);
    speedBox = BoxMeasurement_create(&speedBoxConfig);
    revolutionBox = BoxMeasurement_create(&revolutionBoxConfig);
    heartRateBox = BoxMeasurement_create(&heartRateBoxConfig);
    measurementChart = ChartMeasurement_create(&measurementChartConfig);
    timerLabel = LabelTimer_create(&timerLabelConfig);
}

void TabView_Main_Tab_Live_updateDifficulty(uint32_t difficulty) {
    sprintf(textBuffer, "%ld\nmV", difficulty);

    BoxMeasurement_setValue(&difficultyBox, textBuffer, textBuffer);
}

void TabView_Main_Tab_Live_updateSpeed(uint32_t speed) {
    sprintf(textBuffer, "%ld\nkmh", speed);

    BoxMeasurement_setValue(&speedBox, textBuffer, textBuffer);
}

void TabView_Main_Tab_Live_updateRevolution(uint32_t rpm) {
    sprintf(textBuffer, "%ld\nrpm", rpm);

    BoxMeasurement_setValue(&revolutionBox, textBuffer, textBuffer);
}

void TabView_Main_Tab_Live_updateHeartRate(uint32_t bpm) {
    sprintf(textBuffer, "%ld\nbpm", bpm);

    BoxMeasurement_setValue(&heartRateBox, textBuffer, textBuffer);
}

void TabView_Main_Tab_Live_updateChart(uint8_t updateChart) {
    if (!updateChart) {
        return;
    }

    // TODO: Replace with a proper implementation
    ChartMeasurement_setValue(&measurementChart, lv_rand(70, 90));
}

void TabView_Main_Tab_Live_updateTimer(char* time) { LabelTimer_setValue(&timerLabel, time); }
