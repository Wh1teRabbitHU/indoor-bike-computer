#include "main_screen.h"

static lv_obj_t * mainScreen       = NULL;
static MainScreen_TabView_t active = MAIN_SCREEN_MAIN_TABVIEW;

void MainScreen_init(void) {
    if (mainScreen != NULL) {
        return;
    }

    mainScreen = lv_obj_create(NULL);

    lv_screen_load(mainScreen);
    lv_obj_set_style_bg_color(mainScreen, lv_color_hex(MAIN_SCREEN_BGCOLOR), LV_PART_MAIN);

    MainTabview_Config mainTabConfig = {.screen = mainScreen};

    MainTabview_init(&mainTabConfig);
}

void MainScreen_update(void) {
    MainTabview_update();
}

void MainScreen_handleSelect(void) {
    switch (active) {
    case MAIN_SCREEN_MAIN_TABVIEW:
        MainTabview_handleSelect();
        break;
    }
}

void MainScreen_handleCancel(void) {
    switch (active) {
    case MAIN_SCREEN_MAIN_TABVIEW:
        MainTabview_handleCancel();
        break;
    }
}

void MainScreen_handlePrev(void) {
    switch (active) {
    case MAIN_SCREEN_MAIN_TABVIEW:
        MainTabview_handlePrev();
        break;
    }
}

void MainScreen_handleNext(void) {
    switch (active) {
    case MAIN_SCREEN_MAIN_TABVIEW:
        MainTabview_handleNext();
        break;
    }
}