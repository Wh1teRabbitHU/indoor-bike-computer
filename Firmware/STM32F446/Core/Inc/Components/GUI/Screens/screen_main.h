#ifndef __SCREEN_MAIN_H_
#define __SCREEN_MAIN_H_

#include "tabview_main.h"
#include "lvgl.h"
#include "stdio.h"

#define SCREENMAIN_BGCOLOR 0x000000

void ScreenMain_init(void);
void ScreenMain_updateStates(void);
TabView_Main_State* ScreenMain_getState(void);

#endif