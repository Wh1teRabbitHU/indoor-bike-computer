#ifndef INC_CONTROLS_H_
#define INC_CONTROLS_H_

#include "gui.h"

typedef enum Controls_MenuLevel_t { MENU_LEVEL_TABS, MENU_LEVEL_TAB_CONTROL } Controls_MenuLevel_t;

typedef struct Controls_State {
    GUI_Screen_t screen;
    GUI_Tab_t tab;
    Controls_MenuLevel_t level;
} Controls_State;

void Controls_pressPrev();
void Controls_pressNext();
void Controls_pressCancel();
void Controls_pressSelect();

#endif