#include "er_tft035.h"

static void swap(int16_t *a, int16_t *b) {
    int16_t t = *a;
    *a = *b;
    *b = t;
}

void ER_TFT035_setDataPort(uint32_t data) {
    // D0-D12 = PA0-PA12
    // D13-D17 = PC0-PC4
    uint32_t bottomHalf = data & ER_TFT035_DATA_BOTTOM_MASK;
    uint32_t topHalf = (data >> 13) & ER_TFT035_DATA_TOP_MASK;

    uint32_t bottomResetData = (bottomHalf ^ ER_TFT035_DATA_BOTTOM_MASK) << 16U;
    uint32_t bottomSetData = bottomResetData | bottomHalf;

    uint32_t topResetData = (topHalf ^ ER_TFT035_DATA_TOP_MASK) << 16U;
    uint32_t topSetData = topResetData | topHalf;

    GPIOA->BSRR = bottomSetData;
    GPIOC->BSRR = topSetData;
}

void ER_TFT035_writePixelData(uint32_t data) {
    HAL_GPIO_WritePin(DISPLAY_DC_GPIO_Port, DISPLAY_DC_Pin, 1);
    HAL_GPIO_WritePin(DISPLAY_WR_GPIO_Port, DISPLAY_WR_Pin, 0);

    ER_TFT035_setDataPort(data);

    HAL_GPIO_WritePin(DISPLAY_WR_GPIO_Port, DISPLAY_WR_Pin, 1);
}

void ER_TFT035_writeCommand(uint8_t command) {
    HAL_GPIO_WritePin(DISPLAY_DC_GPIO_Port, DISPLAY_DC_Pin, 0);
    HAL_GPIO_WritePin(DISPLAY_WR_GPIO_Port, DISPLAY_WR_Pin, 0);

    ER_TFT035_setDataPort(command);

    HAL_GPIO_WritePin(DISPLAY_WR_GPIO_Port, DISPLAY_WR_Pin, 1);
}

void ER_TFT035_writeCommandData(uint8_t data) {
    HAL_GPIO_WritePin(DISPLAY_DC_GPIO_Port, DISPLAY_DC_Pin, 1);
    HAL_GPIO_WritePin(DISPLAY_WR_GPIO_Port, DISPLAY_WR_Pin, 0);

    ER_TFT035_setDataPort(data);

    HAL_GPIO_WritePin(DISPLAY_WR_GPIO_Port, DISPLAY_WR_Pin, 1);
}

void ER_TFT035_repeatData(void) {
    HAL_GPIO_WritePin(DISPLAY_WR_GPIO_Port, DISPLAY_WR_Pin, 0);
    HAL_GPIO_WritePin(DISPLAY_WR_GPIO_Port, DISPLAY_WR_Pin, 1);
}

void ER_TFT035_clearScreen(uint32_t bColor) {
    uint16_t i, j;
    ER_TFT035_setCursorToRange(0, 319, 0, 479);
    for (i = 0; i < 320; i++) {
        for (j = 0; j < 480; j++) ER_TFT035_writePixelData(bColor);
    }
}

void ER_TFT035_setCursorToPixel(uint16_t x, uint16_t y) {
    ER_TFT035_writeCommand(0x2A);
    ER_TFT035_writeCommandData(x >> 8);
    ER_TFT035_writeCommandData(x & 0xff);
    ER_TFT035_writeCommandData(x >> 8);
    ER_TFT035_writeCommandData(x & 0xff);
    ER_TFT035_writeCommand(0x2B);
    ER_TFT035_writeCommandData(y >> 8);
    ER_TFT035_writeCommandData(y & 0xff);
    ER_TFT035_writeCommandData(y >> 8);
    ER_TFT035_writeCommandData(y & 0xff);
    ER_TFT035_writeCommand(0x2C);
}

void ER_TFT035_setCursorToRange(uint16_t xStart, uint16_t xEnd, uint16_t yStart, uint16_t yEnd) {
    ER_TFT035_writeCommand(0x2A);
    ER_TFT035_writeCommandData(xStart >> 8);
    ER_TFT035_writeCommandData(xStart & 0xff);
    ER_TFT035_writeCommandData(xEnd >> 8);
    ER_TFT035_writeCommandData(xEnd & 0xff);
    ER_TFT035_writeCommand(0x2B);
    ER_TFT035_writeCommandData(yStart >> 8);
    ER_TFT035_writeCommandData(yStart & 0xff);
    ER_TFT035_writeCommandData(yEnd >> 8);
    ER_TFT035_writeCommandData(yEnd & 0xff);
    ER_TFT035_writeCommand(0x2C);
}

void ER_TFT035_drawPixel(int16_t x, int16_t y, uint32_t color) {
    ER_TFT035_setCursorToPixel(x, y);

    HAL_GPIO_WritePin(DISPLAY_RD_GPIO_Port, DISPLAY_RD_Pin, 1);
    HAL_GPIO_WritePin(DISPLAY_DC_GPIO_Port, DISPLAY_DC_Pin, 1);

    ER_TFT035_setDataPort(color);

    HAL_GPIO_WritePin(DISPLAY_WR_GPIO_Port, DISPLAY_WR_Pin, 0);
    HAL_GPIO_WritePin(DISPLAY_WR_GPIO_Port, DISPLAY_WR_Pin, 1);
}

void ER_TFT035_drawLine(int16_t xStart, int16_t yStart, int16_t xEnd, int16_t yEnd, uint32_t color) {
    int16_t steep = abs(yEnd - yStart) > abs(xEnd - xStart);

    if (steep) {
        swap(&xStart, &yStart);
        swap(&xEnd, &yEnd);
    }

    if (xStart > xEnd) {
        swap(&xStart, &xEnd);
        swap(&yStart, &yEnd);
    }

    int16_t dx, dy;
    dx = xEnd - xStart;
    dy = abs(yEnd - yStart);

    int16_t err = dx / 2;
    int16_t ystep;

    if (yStart < yEnd) {
        ystep = 1;
    } else {
        ystep = -1;
    }

    for (; xStart <= xEnd; xStart++) {
        if (steep) {
            ER_TFT035_drawPixel(yStart, xStart, color);
        } else {
            ER_TFT035_drawPixel(xStart, yStart, color);
        }
        err -= dy;
        if (err < 0) {
            yStart += ystep;
            err += dx;
        }
    }
}

void ER_TFT035_drawRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {
    ER_TFT035_drawLine(x, y, x + width, y, color);
    ER_TFT035_drawLine(x + width, y, x + width, y + height, color);
    ER_TFT035_drawLine(x + width, y + height, x, y + height, color);
    ER_TFT035_drawLine(x, y + height, x, y, color);
}

void ER_TFT035_fillRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {
    ER_TFT035_setCursorToRange(x, x + width - 1, y, y + height - 1);

    HAL_GPIO_WritePin(DISPLAY_RD_GPIO_Port, DISPLAY_RD_Pin, 1);
    HAL_GPIO_WritePin(DISPLAY_DC_GPIO_Port, DISPLAY_DC_Pin, 1);

    ER_TFT035_setDataPort(color);

    for (uint16_t h = 0; h < ER_TFT035_SCREEN_WIDTH; h++) {
        for (uint16_t w = 0; w < ER_TFT035_SCREEN_HEIGHT; w++) {
            HAL_GPIO_WritePin(DISPLAY_WR_GPIO_Port, DISPLAY_WR_Pin, 0);
            HAL_GPIO_WritePin(DISPLAY_WR_GPIO_Port, DISPLAY_WR_Pin, 1);
        }
    }
}

void ER_TFT035_drawCircle(int16_t x0, int16_t y0, int16_t r, uint32_t color) {
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    ER_TFT035_drawPixel(x0, y0 + r, color);
    ER_TFT035_drawPixel(x0, y0 - r, color);
    ER_TFT035_drawPixel(x0 + r, y0, color);
    ER_TFT035_drawPixel(x0 - r, y0, color);

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        ER_TFT035_drawPixel(x0 + x, y0 + y, color);
        ER_TFT035_drawPixel(x0 - x, y0 + y, color);
        ER_TFT035_drawPixel(x0 + x, y0 - y, color);
        ER_TFT035_drawPixel(x0 - x, y0 - y, color);
        ER_TFT035_drawPixel(x0 + y, y0 + x, color);
        ER_TFT035_drawPixel(x0 - y, y0 + x, color);
        ER_TFT035_drawPixel(x0 + y, y0 - x, color);
        ER_TFT035_drawPixel(x0 - y, y0 - x, color);
    }
}

void ER_TFT035_fillCircle(int16_t x0, int16_t y0, int16_t r, uint32_t color) {
    ER_TFT035_drawLine(x0, y0 - r, x0, (y0 - r) + (2 * r + 1) - 1, color);

    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        ER_TFT035_drawLine(x0 + x, y0 - y, x0 + x, y0 - y + 2 * y, color);
        ER_TFT035_drawLine(x0 + y, y0 - x, x0 + y, y0 - x + 2 * x, color);
        ER_TFT035_drawLine(x0 - x, y0 - y, x0 - x, y0 - y + 2 * y, color);
        ER_TFT035_drawLine(x0 - y, y0 - x, x0 - y, y0 - x + 2 * x, color);
    }
}

void ER_TFT035_drawCharacter(uint8_t *font, uint8_t character, uint16_t x, uint16_t y, uint8_t fontSize,
                             uint32_t fontColor, uint32_t bgcolor) {
    uint8_t i, j;
    uint8_t *temp = font;
    uint8_t fontWidth = 8 * fontSize;
    uint8_t fontHeight = 12 * fontSize;

    ER_TFT035_setCursorToRange(x, x + fontWidth - 1, y, y + fontHeight - 1);
    temp += (character - 32) * 12;
    for (j = 0; j < fontHeight; j++) {
        for (i = 0; i < fontWidth; i++) {
            if ((*temp & (1 << (7 - i / fontSize))) != 0) {
                ER_TFT035_writePixelData(fontColor);
            } else {
                ER_TFT035_writePixelData(bgcolor);
            }
        }

        if (j % fontSize == fontSize - 1) {
            temp++;
        }
    }
}

void ER_TFT035_drawText(ER_TFT035_textProps *textProps) {
    char *textPointer = textProps->text;
    uint16_t posX = textProps->posX;
    uint16_t posY = textProps->posY;
    uint8_t fontWidth = 8 * textProps->fontSize;

    while (*textPointer != '\0') {
        ER_TFT035_drawCharacter(textProps->font, *textPointer, posX, posY, textProps->fontSize, textProps->fontColor,
                                textProps->backgroundColor);
        posX += fontWidth - 1;
        textPointer++;
    }
}

void ER_TFT035_init(void) {
    HAL_GPIO_WritePin(DISPLAY_RESET_GPIO_Port, DISPLAY_RESET_Pin, 1);
    HAL_Delay(5);
    HAL_GPIO_WritePin(DISPLAY_RESET_GPIO_Port, DISPLAY_RESET_Pin, 0);
    HAL_Delay(10);
    HAL_GPIO_WritePin(DISPLAY_RESET_GPIO_Port, DISPLAY_RESET_Pin, 1);
    HAL_Delay(120);

    HAL_GPIO_WritePin(DISPLAY_RD_GPIO_Port, DISPLAY_RD_Pin, 1);
    HAL_GPIO_WritePin(DISPLAY_CS_GPIO_Port, DISPLAY_CS_Pin, 0);

    ER_TFT035_writeCommand(0xE0);
    ER_TFT035_writeCommandData(0x00);
    ER_TFT035_writeCommandData(0x03);
    ER_TFT035_writeCommandData(0x09);
    ER_TFT035_writeCommandData(0x08);
    ER_TFT035_writeCommandData(0x16);
    ER_TFT035_writeCommandData(0x0A);
    ER_TFT035_writeCommandData(0x3F);
    ER_TFT035_writeCommandData(0x78);
    ER_TFT035_writeCommandData(0x4C);
    ER_TFT035_writeCommandData(0x09);
    ER_TFT035_writeCommandData(0x0A);
    ER_TFT035_writeCommandData(0x08);
    ER_TFT035_writeCommandData(0x16);
    ER_TFT035_writeCommandData(0x1A);
    ER_TFT035_writeCommandData(0x0F);

    ER_TFT035_writeCommand(0XE1);
    ER_TFT035_writeCommandData(0x00);
    ER_TFT035_writeCommandData(0x16);
    ER_TFT035_writeCommandData(0x19);
    ER_TFT035_writeCommandData(0x03);
    ER_TFT035_writeCommandData(0x0F);
    ER_TFT035_writeCommandData(0x05);
    ER_TFT035_writeCommandData(0x32);
    ER_TFT035_writeCommandData(0x45);
    ER_TFT035_writeCommandData(0x46);
    ER_TFT035_writeCommandData(0x04);
    ER_TFT035_writeCommandData(0x0E);
    ER_TFT035_writeCommandData(0x0D);
    ER_TFT035_writeCommandData(0x35);
    ER_TFT035_writeCommandData(0x37);
    ER_TFT035_writeCommandData(0x0F);

    ER_TFT035_writeCommand(0XC0);      // Power Control 1
    ER_TFT035_writeCommandData(0x17);  // Vreg1out
    ER_TFT035_writeCommandData(0x15);  // Verg2out

    ER_TFT035_writeCommand(0xC1);      // Power Control 2
    ER_TFT035_writeCommandData(0x41);  // VGH,VGL

    ER_TFT035_writeCommand(0xC5);  // Power Control 3
    ER_TFT035_writeCommandData(0x00);
    ER_TFT035_writeCommandData(0x12);  // Vcom
    ER_TFT035_writeCommandData(0x80);

    ER_TFT035_writeCommand(0x36);  // Memory Access
    ER_TFT035_writeCommandData(0x88);

    ER_TFT035_writeCommand(0x3A);      // Interface Pixel Format
    ER_TFT035_writeCommandData(0x66);  // 16 bit

    ER_TFT035_writeCommand(0XB0);  // Interface Mode Control
    ER_TFT035_writeCommandData(0x00);

    ER_TFT035_writeCommand(0xB1);      // Frame rate
    ER_TFT035_writeCommandData(0xA0);  // 60Hz

    ER_TFT035_writeCommand(0xB4);      // Display Inversion Control
    ER_TFT035_writeCommandData(0x02);  // 2-dot

    ER_TFT035_writeCommand(0XB6);  // Display Function Control  RGB/MCU Interface Control

    ER_TFT035_writeCommandData(0x02);  // MCU
    ER_TFT035_writeCommandData(0x02);  // Source,Gate scan dieection

    ER_TFT035_writeCommand(0XE9);      // Set Image Functio
    ER_TFT035_writeCommandData(0x00);  // Disable 24 bit data

    ER_TFT035_writeCommand(0xF7);  // Adjust Control
    ER_TFT035_writeCommandData(0xA9);
    ER_TFT035_writeCommandData(0x51);
    ER_TFT035_writeCommandData(0x2C);
    ER_TFT035_writeCommandData(0x82);  // D7 stream, loose

    ER_TFT035_writeCommand(0x11);  // Sleep out
    HAL_Delay(120);
    ER_TFT035_writeCommand(0x29);
}
