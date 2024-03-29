#include "controls.h"

static GUI_Screen_t activeScreen = GUI_SCREEN_MAIN;

void Controls_pressCancel() {
    switch (activeScreen) {
        case GUI_SCREEN_MAIN:
            ScreenMain_handleCancel();
            break;
    }
}

void Controls_pressSelect() {
    switch (activeScreen) {
        case GUI_SCREEN_MAIN:
            ScreenMain_handleSelect();
            break;
    }
}

void Controls_pressPrev() {
    switch (activeScreen) {
        case GUI_SCREEN_MAIN:
            ScreenMain_handlePrev();
            break;
    }
}

void Controls_pressNext() {
    switch (activeScreen) {
        case GUI_SCREEN_MAIN:
            ScreenMain_handleNext();
            break;
    }
}