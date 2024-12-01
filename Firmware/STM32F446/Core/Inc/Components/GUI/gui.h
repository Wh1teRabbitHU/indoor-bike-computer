#ifndef INC_GUI_H_
#define INC_GUI_H_

#include "er_tft035.h"
#include "lvgl.h"
#include "macros.h"
#include "main_screen.h"
#include "stdio.h"

typedef enum GUI_Screen_t { GUI_MAIN_SCREEN = 0 } GUI_Screen_t;

void GUI_init();
uint32_t GUI_tick();

#endif