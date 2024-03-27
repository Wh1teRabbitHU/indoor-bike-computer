#include "controls.h"

void Controls_pressPrev() {
    uint32_t current = GUI_ScreenMain_getState()->activeTab;

    if (current == 0) {
        current = GUI_TABVIEW_TABCOUNT - 1;
    } else {
        current--;
    }

    GUI_ScreenMain_getState()->activeTab = current;
}

void Controls_pressNext() {
    uint32_t current = GUI_ScreenMain_getState()->activeTab;

    if (current == (GUI_TABVIEW_TABCOUNT - 1)) {
        current = 0;
    } else {
        current++;
    }

    GUI_ScreenMain_getState()->activeTab = current;
}

void Controls_pressCancel() {}

void Controls_pressSelect() {}