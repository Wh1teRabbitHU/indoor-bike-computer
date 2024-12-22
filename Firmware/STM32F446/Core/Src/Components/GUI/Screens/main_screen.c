#include "main_screen.h"

static lv_obj_t * mainScreen = NULL;
static AlertModal alertModal;
static MainScreen_TabView_t active = MAIN_SCREEN_MAIN_TABVIEW;

void MainScreen_init(void) {
    if (mainScreen != NULL) {
        return;
    }

    mainScreen = lv_obj_create(NULL);

    lv_screen_load(mainScreen);
    lv_obj_set_style_bg_color(mainScreen, lv_color_hex(MAIN_SCREEN_BGCOLOR), LV_PART_MAIN);

    MainTabview_Config mainTabConfig   = {.screen = mainScreen};
    AlertModal_Config alertModalConfig = {.screen = mainScreen};

    MainTabview_init(&mainTabConfig);
    alertModal = AlertModal_create(&alertModalConfig);
}

void MainScreen_showAlert(AlertModal_Variant_t variant, uint8_t closable, char * title, char * body) {
    alertModal.variant  = variant;
    alertModal.closable = closable;

    strcpy(alertModal.titleText, title);
    strcpy(alertModal.bodyText, body);

    AlertModal_show(&alertModal);
}

void MainScreen_update(void) {
    MainTabview_update();
    AlertModal_update(&alertModal);
}

void MainScreen_handleSelect(void) {
    if (alertModal.visible) {
        if (alertModal.closable) {
            AlertModal_hide(&alertModal);
        }

        return;
    }

    switch (active) {
    case MAIN_SCREEN_MAIN_TABVIEW:
        MainTabview_handleSelect();
        break;
    }
}

void MainScreen_handleCancel(void) {
    if (alertModal.visible) {
        return;
    }

    switch (active) {
    case MAIN_SCREEN_MAIN_TABVIEW:
        MainTabview_handleCancel();
        break;
    }
}

void MainScreen_handlePrev(void) {
    if (alertModal.visible) {
        return;
    }

    switch (active) {
    case MAIN_SCREEN_MAIN_TABVIEW:
        MainTabview_handlePrev();
        break;
    }
}

void MainScreen_handleNext(void) {
    if (alertModal.visible) {
        return;
    }

    switch (active) {
    case MAIN_SCREEN_MAIN_TABVIEW:
        MainTabview_handleNext();
        break;
    }
}