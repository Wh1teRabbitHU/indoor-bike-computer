#include "gui.h"

static char textBuffer[32];

static GUI_mainScreenState mainScreenState = {.infoMessage = NULL, .errorMessage = NULL, .rpm = 0, .difficulty = 0};

// LVGL
static lv_display_t* display;
static lv_color_t buf1[ER_TFT035_SCREEN_WIDTH * ER_TFT035_SCREEN_HEIGHT / 20];
static uint32_t lastTick = 0;

// LVGL - Components

// Main screen
static lv_obj_t* mainScreen = NULL;
static lv_obj_t* infoLabel = NULL;
static lv_obj_t* errorLabel = NULL;

static lv_obj_t* difficultyLabel = NULL;
static lv_obj_t* rpmLabel = NULL;

// Configuration screen
// TODO

void GUI_handleDisplay(lv_display_t* disp, const lv_area_t* area, lv_color_t* color_p) {
    int32_t x, y;

    ER_TFT035_setCursorToRange(area->x1, area->x2, area->y1, area->y2);

    for (y = area->y1; y <= area->y2; y++) {
        for (x = area->x1; x <= area->x2; x++) {
            volatile uint32_t r = color_p->red;
            volatile uint32_t g = color_p->green;
            volatile uint32_t b = color_p->blue;
            uint32_t color = ((r & 0x3F) << 12) | ((g & 0x3F) << 6) | b;

            ER_TFT035_writePixelData(color);
            color_p++;
        }
    }

    lv_display_flush_ready(disp); /* Indicate you are ready with the flushing*/
}

void GUI_handleKeyboard(lv_indev_t* indev, lv_indev_data_t* data) {
    // TODO: keyboard implementation
}

void GUI_displayInfo() {
    if (mainScreenState.infoMessage == NULL) {
        return;
    }

    if (infoLabel == NULL) {
        infoLabel = lv_label_create(mainScreen);

        lv_obj_set_style_text_color(infoLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
        lv_obj_align(infoLabel, LV_ALIGN_TOP_MID, 0, 16);
        lv_obj_set_width(infoLabel, ER_TFT035_SCREEN_WIDTH * 0.9);
        lv_obj_set_height(infoLabel, ER_TFT035_SCREEN_HEIGHT * 0.2);
    }

    lv_label_set_text(infoLabel, mainScreenState.infoMessage);
}

void GUI_displayError() {
    if (mainScreenState.errorMessage == NULL) {
        return;
    }

    if (errorLabel == NULL) {
        errorLabel = lv_label_create(mainScreen);

        lv_obj_set_style_text_color(errorLabel, lv_color_hex(0xFF0000), LV_PART_MAIN);
        lv_obj_align(errorLabel, LV_ALIGN_BOTTOM_MID, 0, 0);
    }

    lv_label_set_text(errorLabel, mainScreenState.errorMessage);
}

void GUI_displayDifficulty(uint32_t difficulty) {
    sprintf(textBuffer, "Difficulty: %ldmV  ", difficulty);

    if (difficultyLabel == NULL) {
        difficultyLabel = lv_label_create(mainScreen);

        lv_obj_set_style_text_color(difficultyLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
        lv_obj_align(difficultyLabel, LV_ALIGN_CENTER, 0, 0);
    }

    lv_label_set_text(difficultyLabel, textBuffer);
}

void GUI_displayRpm(uint32_t rpm) {
    sprintf(textBuffer, "RPM: %ld/minute  ", rpm);

    if (rpmLabel == NULL) {
        rpmLabel = lv_label_create(mainScreen);

        lv_obj_set_style_text_color(rpmLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
        lv_obj_align(rpmLabel, LV_ALIGN_BOTTOM_MID, 0, 0);
    }

    lv_label_set_text(rpmLabel, textBuffer);
}

void GUI_initDisplay() {
    lv_init();

    display = lv_display_create(ER_TFT035_SCREEN_WIDTH, ER_TFT035_SCREEN_HEIGHT);

    lv_display_set_buffers(display, buf1, NULL, sizeof(buf1), LV_DISPLAY_RENDER_MODE_PARTIAL);
    lv_display_set_flush_cb(display, (lv_display_flush_cb_t)GUI_handleDisplay);
}

void GUI_initMainScreen() {
    mainScreen = lv_obj_create(NULL);

    lv_screen_load(mainScreen);

    lv_obj_set_style_bg_color(mainScreen, lv_color_hex(0x000000), LV_PART_MAIN);
}

void GUI_initInputs() {
    lv_indev_t* indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_KEYPAD); /*See below.*/
    lv_indev_set_read_cb(indev, GUI_handleKeyboard);
}

void GUI_init() {
    ER_TFT035_init();
    ER_TFT035_clearScreen(0x00);

    GUI_initDisplay();
    GUI_initMainScreen();
    GUI_initInputs();
}

void GUI_updateStates() {
    GUI_displayInfo();
    GUI_displayError();
    GUI_displayDifficulty(mainScreenState.difficulty);
    GUI_displayRpm(mainScreenState.rpm);
}

uint32_t GUI_tick() {
    uint32_t currentTick = HAL_GetTick();

    if (lastTick > 0) {
        lv_tick_inc(currentTick - lastTick);
    }

    GUI_updateStates();

    lastTick = HAL_GetTick();

    return lv_timer_handler();
}

void GUI_setInfo(char* info) { mainScreenState.infoMessage = info; }

void GUI_setError(char* error) { mainScreenState.errorMessage = error; }

void GUI_setDifficulty(uint32_t difficulty) { mainScreenState.difficulty = difficulty; }

void GUI_setRpm(uint32_t rpm) { mainScreenState.rpm = rpm; }