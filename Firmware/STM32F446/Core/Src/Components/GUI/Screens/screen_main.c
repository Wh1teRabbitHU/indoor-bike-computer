#include "screen_main.h"

static lv_obj_t* mainScreen = NULL;
static ScreenMain_TabView_t active = SCREENMAIN_TABVIEW_MAIN;

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

void ScreenMain_updateStates(void) { TabView_Main_updateStates(); }

void ScreenMain_handleSelect(void) {
    switch (active) {
        case SCREENMAIN_TABVIEW_MAIN:
            TabView_Main_handleSelect();
            break;
    }
}

void ScreenMain_handleCancel(void) {
    switch (active) {
        case SCREENMAIN_TABVIEW_MAIN:
            TabView_Main_handleCancel();
            break;
    }
}

void ScreenMain_handlePrev(void) {
    switch (active) {
        case SCREENMAIN_TABVIEW_MAIN:
            TabView_Main_handlePrev();
            break;
    }
}

void ScreenMain_handleNext(void) {
    switch (active) {
        case SCREENMAIN_TABVIEW_MAIN:
            TabView_Main_handleNext();
            break;
    }
}