#include "controls.h"

// static Controls_State state = {.screen = GUI_SCREEN_MAIN, .tab = TABVIEW_MAIN_TAB_LIVE, .level = MENU_LEVEL_TABS};

void Controls_pressPrev() {
    uint32_t current = ScreenMain_getState()->activeTab;

    if (current == 0) {
        current = GUI_TABVIEW_TABCOUNT - 1;
    } else {
        current--;
    }

    ScreenMain_getState()->activeTab = current;
}

void Controls_pressNext() {
    uint32_t current = ScreenMain_getState()->activeTab;

    if (current == (GUI_TABVIEW_TABCOUNT - 1)) {
        current = 0;
    } else {
        current++;
    }

    ScreenMain_getState()->activeTab = current;
}

void Controls_pressCancel() {}

void Controls_pressSelect() {}