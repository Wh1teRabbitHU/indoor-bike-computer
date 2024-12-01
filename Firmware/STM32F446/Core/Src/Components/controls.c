#include "controls.h"

static GUI_Screen_t activeScreen = GUI_MAIN_SCREEN;

void Controls_pressCancel() {
    switch (activeScreen) {
    case GUI_MAIN_SCREEN:
        MainScreen_handleCancel();
        break;
    }
}

void Controls_pressSelect() {
    switch (activeScreen) {
    case GUI_MAIN_SCREEN:
        MainScreen_handleSelect();
        break;
    }
}

void Controls_pressPrev() {
    switch (activeScreen) {
    case GUI_MAIN_SCREEN:
        MainScreen_handlePrev();
        break;
    }
}

void Controls_pressNext() {
    switch (activeScreen) {
    case GUI_MAIN_SCREEN:
        MainScreen_handleNext();
        break;
    }
}