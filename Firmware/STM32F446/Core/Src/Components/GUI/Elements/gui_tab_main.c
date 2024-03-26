#include "gui_tab_main.h"

static GUI_TabMain_t active = GUI_TAB_MAIN;

GUI_TabMain GUI_TabMain_create(GUI_TabMain_Config* config) {
    GUI_TabMain tabInstance = {.tabs = {0}};

    lv_obj_t* tabView = lv_tabview_create(config->screen);

    lv_obj_set_style_bg_color(tabView, lv_color_hex(GUI_TABVIEW_TABMAIN_BGCOLOR), 0);
    lv_tabview_set_tab_bar_position(tabView, LV_DIR_BOTTOM);
    lv_tabview_set_tab_bar_size(tabView, config->height);

    lv_obj_t* tabMain = lv_tabview_add_tab(tabView, "Live");
    lv_obj_t* tabHistory = lv_tabview_add_tab(tabView, "Hist.");
    lv_obj_t* tabSettings = lv_tabview_add_tab(tabView, "Set.");

    lv_obj_set_style_pad_all(tabMain, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_color(tabMain, lv_color_hex(GUI_TABVIEW_TABMAIN_BGCOLOR), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(tabMain, LV_OPA_COVER, 0);

    lv_obj_set_style_pad_all(tabHistory, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_color(tabHistory, lv_color_hex(GUI_TABVIEW_TABHISTORY_BGCOLOR), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(tabHistory, LV_OPA_COVER, 0);

    lv_obj_set_style_pad_all(tabSettings, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_color(tabSettings, lv_color_hex(GUI_TABVIEW_TABSETTINGS_BGCOLOR), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(tabSettings, LV_OPA_COVER, 0);

    tabInstance.tabView = tabView;

    tabInstance.tabs[GUI_TAB_MAIN] = tabMain;
    tabInstance.tabs[GUI_TAB_HISTORY] = tabHistory;
    tabInstance.tabs[GUI_TAB_SETTINGS] = tabSettings;

    tabInstance.active = GUI_TAB_MAIN;

    GUI_TabMain_setActive(&tabInstance, active);

    return tabInstance;
}

void GUI_TabMain_setActive(GUI_TabMain* instance, GUI_TabMain_t tab) {
    instance->active = tab;

    lv_tabview_set_active(instance->tabView, instance->active, LV_ANIM_OFF);
}

void GUI_TabMain_prevTab(GUI_TabMain* instance) {
    uint32_t current = instance->active;

    if (current == 0) {
        current = GUI_TABVIEW_TABCOUNT - 1;
    } else {
        current--;
    }

    GUI_TabMain_setActive(instance, current);
}

void GUI_TabMain_nextTab(GUI_TabMain* instance) {
    uint32_t current = instance->active;

    if (current == (GUI_TABVIEW_TABCOUNT - 1)) {
        current = 0;
    } else {
        current++;
    }

    GUI_TabMain_setActive(instance, current);
}