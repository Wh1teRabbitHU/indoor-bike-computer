#ifndef __SCREEN_MAIN_H_
#define __SCREEN_MAIN_H_

#include "lvgl.h"
#include "stdio.h"
#include "tabview_main.h"

#define SCREENMAIN_BGCOLOR 0x000000

typedef enum ScreenMain_TabView_t { SCREENMAIN_TABVIEW_MAIN = 0 } ScreenMain_TabView_t;

void ScreenMain_init(void);
void ScreenMain_update(void);

// Control handlers
void ScreenMain_handleSelect(void);
void ScreenMain_handleCancel(void);
void ScreenMain_handlePrev(void);
void ScreenMain_handleNext(void);

#endif