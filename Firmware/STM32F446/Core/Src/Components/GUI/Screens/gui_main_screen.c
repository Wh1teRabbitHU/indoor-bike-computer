#include "gui_main_screen.h"

#include "gui_box_measurement.h"
#include "gui_chart_measurement.h"

static char textBuffer[32];

static lv_obj_t* mainScreen = NULL;

static GUI_BoxMeasurement difficultyBox;
static GUI_BoxMeasurement speedBox;
static GUI_BoxMeasurement revolutionBox;
static GUI_BoxMeasurement heartRateBox;
static GUI_ChartMeasurement measurementChart;

static GUI_MainScreen_State state = {
    .infoMessage = NULL, .errorMessage = NULL, .difficulty = 0, .speed = 0, .rpm = 0, .bpm = 0};

void GUI_MainScreen_initElements(void) {
    GUI_BoxMeasurement_Config difficultyBoxConfig = {
        .screen = mainScreen, .title = "Difficulty", .x = 10, .y = 40, .bgColor = 0xBCC7FF};
    GUI_BoxMeasurement_Config speedBoxConfig = {
        .screen = mainScreen, .title = "Speed", .x = 165, .y = 40, .bgColor = 0x77EEE6};
    GUI_BoxMeasurement_Config revolutionBoxConfig = {
        .screen = mainScreen, .title = "Revolution", .x = 10, .y = 150, .bgColor = 0xBFFFA1};
    GUI_BoxMeasurement_Config heartRateBoxConfig = {
        .screen = mainScreen, .title = "Heart Rate", .x = 165, .y = 150, .bgColor = 0xFFA490};
    GUI_ChartMeasurement_Config measurementChartConfig = {
        .screen = mainScreen, .x = 10, .y = 280, .mainColor = 0xEAEAEA, .series1Color = 0x39B200};

    difficultyBox = GUI_BoxMeasurement_create(&difficultyBoxConfig);
    speedBox = GUI_BoxMeasurement_create(&speedBoxConfig);
    revolutionBox = GUI_BoxMeasurement_create(&revolutionBoxConfig);
    heartRateBox = GUI_BoxMeasurement_create(&heartRateBoxConfig);
    measurementChart = GUI_ChartMeasurement_create(&measurementChartConfig);
}

void GUI_MainScreen_init(void) {
    if (mainScreen != NULL) {
        return;
    }

    mainScreen = lv_obj_create(NULL);

    lv_screen_load(mainScreen);
    lv_obj_set_style_bg_color(mainScreen, lv_color_hex(GUI_MAINSCREEN_BGCOLOR), LV_PART_MAIN);

    GUI_MainScreen_initElements();
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
    // TODO: Replace with a proper implementation
    GUI_ChartMeasurement_setValue(&measurementChart, lv_rand(50, 60));
}

void GUI_MainScreen_updateStates(void) {
    GUI_displayDifficulty(state.difficulty);
    GUI_displaySpeed(state.speed);
    GUI_displayRevolution(state.rpm);
    GUI_displayHeartRate(state.bpm);
    GUI_displayMeasurementChart();
}

GUI_MainScreen_State* GUI_MainScreen_getState(void) { return &state; }