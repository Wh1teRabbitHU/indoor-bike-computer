#ifndef __LABEL_PAGE_HEADER_H_
#define __LABEL_PAGE_HEADER_H_

#include "lvgl.h"
#include "stdio.h"

#define LABEL_PAGE_HEADER_WIDTH 310
#define LABEL_PAGE_HEADER_HEIGHT 40
#define LABEL_PAGE_HEADER_TEXT_COLOR 0xFFFFFF
#define LABEL_PAGE_HEADER_BG_COLOR 0x000000

typedef struct LabelPageHeader {
    lv_obj_t* box;
    lv_obj_t* selectionLabel;
    lv_obj_t* rangeLabel;
    uint32_t selectedIndex;
    uint32_t elementCount;
    uint32_t pageStart;
    uint32_t pageEnd;
} LabelPageHeader;

typedef struct LabelPageHeader_Config {
    lv_obj_t* screen;
    char* name;
    int32_t x;
    int32_t y;
} LabelPageHeader_Config;

LabelPageHeader LabelPageHeader_create(LabelPageHeader_Config* config);
void LabelPageHeader_update(LabelPageHeader* instance);

#endif
