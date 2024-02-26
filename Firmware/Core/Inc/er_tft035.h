#ifndef __ER_TFT035_H
#define __ER_TFT035_H

#include "main.h"
#include "stdint.h"

#define ER_TFT035_SCREEN_WIDTH 320
#define ER_TFT035_SCREEN_HEIGHT 480

#define ER_TFT035_DATA_BOTTOM_MASK ((1 << 13) - 1)
#define ER_TFT035_DATA_TOP_MASK ((1 << 5) - 1)

#define CONVERT_24BIT_COLOR(rgbValue) \
    (((rgbValue >> 18) & 0b111111) << 12) | (((rgbValue >> 10) & 0b111111) << 6) | ((rgbValue >> 2) & 0b111111)

void ER_TFT035_init(void);
void ER_TFT035_clear(uint32_t bgColor);
void ER_TFT035_setCursorToRange(uint16_t xStart, uint16_t xEnd, uint16_t yStart, uint16_t yEnd);
void ER_TFT035_fillRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

#endif