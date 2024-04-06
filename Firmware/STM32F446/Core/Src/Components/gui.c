#include "gui.h"

// LVGL
static lv_display_t* display;
static lv_color_t buf1[ER_TFT035_SCREEN_WIDTH * ER_TFT035_SCREEN_HEIGHT / 20];
static uint32_t lastTick = 0;
// static GUI_Screen_t activeScreen = GUI_SCREEN_MAIN;

PRIVATE uint32_t GUI_getColor(lv_color_t* color_p) {
    uint32_t r = color_p->red;
    uint32_t g = color_p->green;
    uint32_t b = color_p->blue;
    uint32_t color = ((r >> 2) << 12) | ((g >> 2) << 6) | (b >> 2);

    return color;
}

void GUI_handleDisplay(lv_display_t* disp, const lv_area_t* area, lv_color_t* color_p) {
    int32_t x, y;
    uint32_t prevColor = GUI_getColor(color_p) + 1;  // Making sure that the first time it's a different color

    ER_TFT035_setCursorToRange(area->x1, area->x2, area->y1, area->y2);

    for (y = area->y1; y <= area->y2; y++) {
        for (x = area->x1; x <= area->x2; x++) {
            uint32_t currentColor = GUI_getColor(color_p);

            if (currentColor == prevColor) {
                ER_TFT035_repeatData();
            } else {
                ER_TFT035_writePixelData(currentColor);
            }

            prevColor = currentColor;
            color_p++;
        }
    }

    lv_display_flush_ready(disp); /* Indicate you are ready with the flushing*/
}

void GUI_handleKeyboard(lv_indev_t* indev, lv_indev_data_t* data) {
    // TODO: keyboard implementation
}

void GUI_initDisplay() {
    lv_init();

    display = lv_display_create(ER_TFT035_SCREEN_WIDTH, ER_TFT035_SCREEN_HEIGHT);

    lv_display_set_buffers(display, buf1, NULL, sizeof(buf1), LV_DISPLAY_RENDER_MODE_PARTIAL);
    lv_display_set_flush_cb(display, (lv_display_flush_cb_t)GUI_handleDisplay);
}

void GUI_init() {
    ER_TFT035_init();
    ER_TFT035_clearScreen(0x00);

    GUI_initDisplay();

    ScreenMain_init();
}

uint32_t GUI_tick() {
    uint32_t currentTick = HAL_GetTick();

    if (lastTick > 0) {
        lv_tick_inc(currentTick - lastTick);
    }

    ScreenMain_update();

    lastTick = HAL_GetTick();

    return lv_timer_handler();
}