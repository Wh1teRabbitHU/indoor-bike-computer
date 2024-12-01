#ifndef __MAIN_SCREEN_H_
#define __MAIN_SCREEN_H_

#include "lvgl.h"
#include "main_tabview.h"
#include "stdio.h"

#define MAIN_SCREEN_BGCOLOR 0x000000

typedef enum MainScreen_TabView_t { MAIN_SCREEN_MAIN_TABVIEW = 0 } MainScreen_TabView_t;

void MainScreen_init(void);
void MainScreen_update(void);

// Control handlers
void MainScreen_handleSelect(void);
void MainScreen_handleCancel(void);
void MainScreen_handlePrev(void);
void MainScreen_handleNext(void);

#endif