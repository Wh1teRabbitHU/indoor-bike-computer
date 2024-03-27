#ifndef __GUI_TAB_MAIN_H_
#define __GUI_TAB_MAIN_H_

#include "lvgl.h"

#define GUI_TABVIEW_TABCOUNT 3
#define GUI_TABVIEW_TABMAIN_BGCOLOR 0x000000
#define GUI_TABVIEW_TABHISTORY_BGCOLOR 0x000000
#define GUI_TABVIEW_TABSETTINGS_BGCOLOR 0x000000

typedef enum GUI_Tab_t { GUI_TAB_MAIN = 0, GUI_TAB_HISTORY = 1, GUI_TAB_SETTINGS = 2 } GUI_Tab_t;

typedef struct GUI_TabMain {
    lv_obj_t* tabView;
    lv_obj_t* tabs[GUI_TABVIEW_TABCOUNT];
    GUI_Tab_t active;
} GUI_TabMain;

typedef struct GUI_TabMain_Config {
    lv_obj_t* screen;
    int32_t height;
    uint32_t bgColor;
} GUI_TabMain_Config;

GUI_TabMain GUI_TabMain_create(GUI_TabMain_Config* config);
void GUI_TabMain_setActive(GUI_TabMain* instance, GUI_Tab_t tab);
void GUI_TabMain_prevTab(GUI_TabMain* instance);
void GUI_TabMain_nextTab(GUI_TabMain* instance);

#endif