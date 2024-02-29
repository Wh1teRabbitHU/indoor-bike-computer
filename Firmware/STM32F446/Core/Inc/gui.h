#ifndef INC_GUI_H_
#define INC_GUI_H_

#include "er_tft035.h"

void GUI_logInfo(char* info);
void GUI_logError(char* error);

void GUI_displayDifficulty(uint32_t difficulty);
void GUI_displayRpm(uint32_t rpm);

#endif