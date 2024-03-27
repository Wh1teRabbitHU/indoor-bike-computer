#include "screen_main.h"

static lv_obj_t* mainScreen = NULL;

static TabView_Main_State state = {
    .infoMessage = NULL, .errorMessage = NULL, .difficulty = 0, .speed = 0, .rpm = 0, .bpm = 0};

void ScreenMain_init(void) {
    if (mainScreen != NULL) {
        return;
    }

    mainScreen = lv_obj_create(NULL);

    lv_screen_load(mainScreen);
    lv_obj_set_style_bg_color(mainScreen, lv_color_hex(SCREENMAIN_BGCOLOR), LV_PART_MAIN);

    TabView_Main_Config mainTabConfig = {.screen = mainScreen, .height = 40};

    TabView_Main_init(&mainTabConfig);
}

void ScreenMain_updateStates(void) { TabView_Main_updateStates(&state); }

TabView_Main_State* ScreenMain_getState(void) { return &state; }