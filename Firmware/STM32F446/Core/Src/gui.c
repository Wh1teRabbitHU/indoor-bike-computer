#include "gui.h"

#include "font_6_12.h"

static char textBuffer[32];

void GUI_logInfo(char* info) {
    ER_TFT035_textProps infoText = {.font = fontData,
                                    .text = info,
                                    .posX = 10,
                                    .posY = 10,
                                    .fontSize = 2,
                                    .fontColor = CONVERT_24BIT_COLOR(0x000000),
                                    .backgroundColor = CONVERT_24BIT_COLOR(0xFFFFFF)};

    ER_TFT035_drawText(&infoText);
}

void GUI_logError(char* error) {
    ER_TFT035_textProps errorText = {.font = fontData,
                                     .text = error,
                                     .posX = 10,
                                     .posY = 10,
                                     .fontSize = 2,
                                     .fontColor = CONVERT_24BIT_COLOR(0xFF0000),
                                     .backgroundColor = CONVERT_24BIT_COLOR(0xFFFFFF)};

    ER_TFT035_drawText(&errorText);
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