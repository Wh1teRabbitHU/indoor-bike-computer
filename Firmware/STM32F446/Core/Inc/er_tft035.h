#ifndef __ER_TFT035_H
#define __ER_TFT035_H

#include "main.h"
#include "stdint.h"
#include "stdlib.h"

#define ER_TFT035_SCREEN_WIDTH 320
#define ER_TFT035_SCREEN_HEIGHT 480

#define ER_TFT035_DATA_BOTTOM_MASK ((1 << 13) - 1)
#define ER_TFT035_DATA_TOP_MASK ((1 << 5) - 1)

#define CONVERT_24BIT_COLOR(rgbValue) \
    (((rgbValue >> 18) & 0b111111) << 12) | (((rgbValue >> 10) & 0b111111) << 6) | ((rgbValue >> 2) & 0b111111)

typedef struct ER_TFT035_textProps {
    uint8_t *font;
    char *text;
    uint16_t posX;
    uint16_t posY;
    uint16_t fontSize;
    uint32_t fontColor;
    uint32_t backgroundColor;
} ER_TFT035_textProps;

void ER_TFT035_init(void);
void ER_TFT035_clearScreen(uint32_t bgColor);
void ER_TFT035_setCursorToPixel(uint16_t x, uint16_t y);
void ER_TFT035_setCursorToRange(uint16_t xStart, uint16_t xEnd, uint16_t yStart, uint16_t yEnd);
void ER_TFT035_drawPixel(int16_t x, int16_t y, uint32_t color);
void ER_TFT035_drawLine(int16_t xStart, int16_t yStart, int16_t xEnd, int16_t yEnd, uint32_t color);
void ER_TFT035_drawRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);
void ER_TFT035_fillRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);
void ER_TFT035_drawCircle(int16_t x0, int16_t y0, int16_t r, uint32_t color);
void ER_TFT035_fillCircle(int16_t x0, int16_t y0, int16_t r, uint32_t color);
void ER_TFT035_drawCharacter(uint8_t *font, uint8_t character, uint16_t x, uint16_t y, uint8_t fontSize,
                             uint32_t fontColor, uint32_t bgcolor);
void ER_TFT035_drawText(ER_TFT035_textProps *textProps);

#endif