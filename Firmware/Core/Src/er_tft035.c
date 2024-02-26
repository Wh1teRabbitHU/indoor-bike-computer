#include "er_tft035.h"

void ER_TFT035_setPixelDataPort(uint32_t data) {
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
    HAL_GPIO_WritePin(DISPLAY_CS_GPIO_Port, DISPLAY_CS_Pin, 0);
    HAL_GPIO_WritePin(DISPLAY_WR_GPIO_Port, DISPLAY_WR_Pin, 0);

    ER_TFT035_setPixelDataPort(data);

    HAL_GPIO_WritePin(DISPLAY_WR_GPIO_Port, DISPLAY_WR_Pin, 1);
    HAL_GPIO_WritePin(DISPLAY_CS_GPIO_Port, DISPLAY_CS_Pin, 1);
}

void ER_TFT035_writeCommandData(uint8_t data) {
    HAL_GPIO_WritePin(DISPLAY_DC_GPIO_Port, DISPLAY_DC_Pin, 1);
    HAL_GPIO_WritePin(DISPLAY_CS_GPIO_Port, DISPLAY_CS_Pin, 0);
    HAL_GPIO_WritePin(DISPLAY_WR_GPIO_Port, DISPLAY_WR_Pin, 0);

    ER_TFT035_setPixelDataPort(data);

    HAL_GPIO_WritePin(DISPLAY_WR_GPIO_Port, DISPLAY_WR_Pin, 1);
    HAL_GPIO_WritePin(DISPLAY_CS_GPIO_Port, DISPLAY_CS_Pin, 1);
}

void ER_TFT035_writeCommand(uint8_t command) {
    HAL_GPIO_WritePin(DISPLAY_DC_GPIO_Port, DISPLAY_DC_Pin, 0);
    HAL_GPIO_WritePin(DISPLAY_CS_GPIO_Port, DISPLAY_CS_Pin, 0);
    HAL_GPIO_WritePin(DISPLAY_WR_GPIO_Port, DISPLAY_WR_Pin, 0);

    ER_TFT035_setPixelDataPort(command);

    HAL_GPIO_WritePin(DISPLAY_WR_GPIO_Port, DISPLAY_WR_Pin, 1);
    HAL_GPIO_WritePin(DISPLAY_CS_GPIO_Port, DISPLAY_CS_Pin, 1);
}

void ER_TFT035_clear(uint32_t bColor) {
    uint16_t i, j;
    ER_TFT035_setCursorToRange(0, 319, 0, 479);
    for (i = 0; i < 320; i++) {
        for (j = 0; j < 480; j++) ER_TFT035_writePixelData(bColor);
    }
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

void ER_TFT035_fillRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {
    ER_TFT035_setCursorToRange(x, x + width - 1, y, y + height - 1);

    HAL_GPIO_WritePin(DISPLAY_CS_GPIO_Port, DISPLAY_CS_Pin, 0);
    HAL_GPIO_WritePin(DISPLAY_RD_GPIO_Port, DISPLAY_RD_Pin, 1);
    HAL_GPIO_WritePin(DISPLAY_DC_GPIO_Port, DISPLAY_DC_Pin, 1);

    ER_TFT035_setPixelDataPort(color);

    for (uint16_t h = 0; h < ER_TFT035_SCREEN_WIDTH; h++) {
        for (uint16_t w = 0; w < ER_TFT035_SCREEN_HEIGHT; w++) {
            HAL_GPIO_WritePin(DISPLAY_WR_GPIO_Port, DISPLAY_WR_Pin, 0);
            HAL_GPIO_WritePin(DISPLAY_WR_GPIO_Port, DISPLAY_WR_Pin, 1);
        }
    }

    HAL_GPIO_WritePin(DISPLAY_CS_GPIO_Port, DISPLAY_CS_Pin, 1);
}

void ER_TFT035_init(void) {
    HAL_GPIO_WritePin(DISPLAY_RESET_GPIO_Port, DISPLAY_RESET_Pin, 1);
    HAL_Delay(5);
    HAL_GPIO_WritePin(DISPLAY_RESET_GPIO_Port, DISPLAY_RESET_Pin, 0);
    HAL_Delay(10);
    HAL_GPIO_WritePin(DISPLAY_RESET_GPIO_Port, DISPLAY_RESET_Pin, 1);
    HAL_Delay(120);

    HAL_GPIO_WritePin(DISPLAY_RD_GPIO_Port, DISPLAY_RD_Pin, 1);

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
    ER_TFT035_writeCommandData(0x48);

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
