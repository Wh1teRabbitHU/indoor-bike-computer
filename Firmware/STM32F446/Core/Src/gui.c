#include "gui.h"

#include "font_6_12.h"

static char textBuffer[32];
static uint32_t lastTick = 0;

// LVGL
static lv_display_t* display;
static lv_color_t buf1[ER_TFT035_SCREEN_WIDTH * ER_TFT035_SCREEN_HEIGHT / 10];

// LVGL - Components

// Main screen
static lv_obj_t* mainScreen = NULL;
static lv_obj_t* infoLabel = NULL;
static lv_obj_t* errorLabel = NULL;

// Configuration screen
// TODO

void GUI_handleDisplay(lv_display_t* disp, const lv_area_t* area, lv_color_t* color_p) {
    int32_t x, y;

    ER_TFT035_setCursorToRange(area->x1, area->x2, area->y1, area->y2);

    for (y = area->y1; y <= area->y2; y++) {
        for (x = area->x1; x <= area->x2; x++) {
            uint32_t color = CONVERT_24BIT_COLOR((color_p->red << 16) | (color_p->green << 8) | color_p->blue);
            ER_TFT035_writePixelData(color);
            color_p++;
        }
    }

    lv_display_flush_ready(disp); /* Indicate you are ready with the flushing*/
}

void GUI_handleKeyboard(lv_indev_t* indev, lv_indev_data_t* data) {
    // TODO: keyboard implementation
    // data->key = last_key();

    // if (key_pressed())
    //     data->state = LV_INDEV_STATE_PRESSED;
    // else
    //     data->state = LV_INDEV_STATE_RELEASED;
    data->state = LV_INDEV_STATE_RELEASED;
}

void GUI_initDisplay() {
    lv_init();

    display = lv_display_create(ER_TFT035_SCREEN_WIDTH, ER_TFT035_SCREEN_HEIGHT);

    lv_display_set_buffers(display, buf1, NULL, sizeof(buf1), LV_DISPLAY_RENDER_MODE_PARTIAL);
    lv_display_set_flush_cb(display, GUI_handleDisplay);
}

void GUI_initMainScreen() {
    mainScreen = lv_obj_create(NULL);

    lv_screen_load(mainScreen);

    lv_obj_set_style_bg_color(mainScreen, lv_color_hex(0x003a57), LV_PART_MAIN);
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

void GUI_tick() {
    uint32_t currentTick = HAL_GetTick();

    if (lastTick > 0) {
        lv_tick_inc(currentTick - lastTick);
    }

    lastTick = HAL_GetTick();

    lv_timer_handler();
}

void GUI_logInfo(char* info) {
    if (infoLabel == NULL) {
        infoLabel = lv_label_create(mainScreen);

        lv_obj_set_style_text_color(mainScreen, lv_color_hex(0xffffff), LV_PART_MAIN);
        lv_obj_align(infoLabel, LV_ALIGN_BOTTOM_MID, 0, 0);
    }

    lv_label_set_text(infoLabel, info);
}

void GUI_logError(char* error) {
    if (errorLabel == NULL) {
        errorLabel = lv_label_create(mainScreen);

        lv_obj_set_style_text_color(mainScreen, lv_color_hex(0xff0000), LV_PART_MAIN);
        lv_obj_align(errorLabel, LV_ALIGN_BOTTOM_MID, 0, 0);
    }

    lv_label_set_text(errorLabel, error);
}

void GUI_displayDifficulty(uint32_t difficulty) {
    sprintf(textBuffer, "Difficulty: %ldmV  ", difficulty);

    ER_TFT035_textProps infoText = {.font = fontData,
                                    .text = textBuffer,
                                    .posX = 10,
                                    .posY = 10,
                                    .fontSize = 2,
                                    .fontColor = CONVERT_24BIT_COLOR(0x000000),
                                    .backgroundColor = CONVERT_24BIT_COLOR(0xFFFFFF)};

    ER_TFT035_drawText(&infoText);
}

void GUI_displayRpm(uint32_t rpm) {
    sprintf(textBuffer, "RPM: %ld/minute  ", rpm);

    ER_TFT035_textProps infoText = {.font = fontData,
                                    .text = textBuffer,
                                    .posX = 10,
                                    .posY = 50,
                                    .fontSize = 2,
                                    .fontColor = CONVERT_24BIT_COLOR(0x000000),
                                    .backgroundColor = CONVERT_24BIT_COLOR(0xFFFFFF)};

    ER_TFT035_drawText(&infoText);
}