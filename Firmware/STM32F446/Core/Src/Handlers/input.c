#include "input.h"

static GUI_Screen_t activeScreen = GUI_MAIN_SCREEN;

void Input_pressCancel() {
    switch (activeScreen) {
    case GUI_MAIN_SCREEN:
        MainScreen_handleCancel();
        break;
    }
}

void Input_pressSelect() {
    switch (activeScreen) {
    case GUI_MAIN_SCREEN:
        MainScreen_handleSelect();
        break;
    }
}

void Input_pressPrev() {
    switch (activeScreen) {
    case GUI_MAIN_SCREEN:
        MainScreen_handlePrev();
        break;
    }
}

void Input_pressNext() {
    switch (activeScreen) {
    case GUI_MAIN_SCREEN:
        MainScreen_handleNext();
        break;
    }
}