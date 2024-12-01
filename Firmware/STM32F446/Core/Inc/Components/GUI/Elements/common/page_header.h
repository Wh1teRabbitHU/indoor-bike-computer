#ifndef __PAGE_HEADER_H_
#define __PAGE_HEADER_H_

#include "lvgl.h"
#include "stdio.h"

#define PAGE_HEADER_WIDTH      310
#define PAGE_HEADER_HEIGHT     40
#define PAGE_HEADER_TEXT_COLOR 0xFFFFFF
#define PAGE_HEADER_BG_COLOR   0x000000

typedef struct PageHeader {
    lv_obj_t * box;
    lv_obj_t * selectionLabel;
    lv_obj_t * rangeLabel;
    uint32_t selectedIndex;
    uint32_t elementCount;
    uint32_t pageStart;
    uint32_t pageEnd;
} PageHeader;

typedef struct PageHeader_Config {
    lv_obj_t * screen;
    char * name;
    int32_t x;
    int32_t y;
} PageHeader_Config;

PageHeader PageHeader_create(PageHeader_Config * config);
void PageHeader_update(PageHeader * instance);

#endif
