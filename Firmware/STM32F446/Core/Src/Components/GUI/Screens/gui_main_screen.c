#include "gui_main_screen.h"

#include "gui_box_measurement.h"

static char textBuffer[32];

static lv_obj_t* mainScreen = NULL;

static GUI_BoxMeasurement_t difficultyBox;
static GUI_BoxMeasurement_t speedBox;
static GUI_BoxMeasurement_t revolutionBox;
static GUI_BoxMeasurement_t heartRateBox;

static GUI_MainScreen_State state = {
    .infoMessage = NULL, .errorMessage = NULL, .difficulty = 0, .speed = 0, .rpm = 0, .bpm = 0};

void GUI_MainScreen_initElements(void) {
    difficultyBox = GUI_BoxMeasurement_create(mainScreen, 10, 40);
    speedBox = GUI_BoxMeasurement_create(mainScreen, 165, 40);
    revolutionBox = GUI_BoxMeasurement_create(mainScreen, 10, 150);
    heartRateBox = GUI_BoxMeasurement_create(mainScreen, 165, 150);
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

    GUI_BoxMeasurement_setValue(&difficultyBox, textBuffer);
}

void GUI_displaySpeed(uint32_t speed) {
    sprintf(textBuffer, "%ld\nkm/h", speed);

    GUI_BoxMeasurement_setValue(&speedBox, textBuffer);
}

void GUI_displayRevolution(uint32_t rpm) {
    sprintf(textBuffer, "%ld\nrpm", rpm);

    GUI_BoxMeasurement_setValue(&revolutionBox, textBuffer);
}

void GUI_displayHeartRate(uint32_t bpm) {
    sprintf(textBuffer, "%ld\nbpm", bpm);

    GUI_BoxMeasurement_setValue(&heartRateBox, textBuffer);
}

void GUI_MainScreen_updateStates(void) {
    GUI_displayDifficulty(state.difficulty);
    GUI_displaySpeed(state.speed);
    GUI_displayRevolution(state.rpm);
    GUI_displayHeartRate(state.bpm);
}

GUI_MainScreen_State* GUI_MainScreen_getState(void) { return &state; }