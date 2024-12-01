#ifndef __RUN_LIST_ITEM_H_
#define __RUN_LIST_ITEM_H_

#include "data.h"
#include "lvgl.h"

#define RUN_LIST_ITEM_WIDTH                 310
#define RUN_LIST_ITEM_HEIGHT                76
#define RUN_LIST_ITEM_MARGIN                5
#define RUN_LIST_ITEM_DEFAULT_BG_COLOR      0xE1F6FF
#define RUN_LIST_ITEM_SELECTED_BG_COLOR     0x9EACB3
#define RUN_LIST_ITEM_DEFAULT_BORDER_COLOR  0xE1F6FF
#define RUN_LIST_ITEM_SELECTED_BORDER_COLOR 0x717b80

typedef struct RunListItem {
    lv_obj_t * box;
    lv_obj_t * nameLabel;
    lv_obj_t * createdLabel;
    lv_obj_t * sessionLengthLabel;
    lv_obj_t * distanceLabel;
} RunListItem;

typedef struct RunListItem_Config {
    lv_obj_t * screen;
    int32_t x;
    int32_t y;
} RunListItem_Config;

RunListItem RunListItem_create(RunListItem_Config * config);
void RunListItem_changeSelection(RunListItem * instance, uint8_t selected);
void RunListItem_setRun(RunListItem * instance, Data_Run * run);
void RunListItem_clearRun(RunListItem * instance);
void RunListItem_show(RunListItem * instance);
void RunListItem_hide(RunListItem * instance);

#endif