#ifndef __BOX_RUN_DETAILS_H_
#define __BOX_RUN_DETAILS_H_

#include "data.h"
#include "lvgl.h"

#define BUX_RUN_DETAILS_WIDTH 300
#define BUX_RUN_DETAILS_HEIGHT 50
#define BUX_RUN_DETAILS_MARGIN 5

typedef struct BoxRunDetails {
    lv_obj_t* box;
    lv_obj_t* nameLabel;
    lv_obj_t* createdLabel;
    lv_obj_t* sessionLengthLabel;
    lv_obj_t* distanceLabel;
} BoxRunDetails;

typedef struct BoxRunDetails_Config {
    lv_obj_t* screen;
    int32_t x;
    int32_t y;
} BoxRunDetails_Config;

BoxRunDetails BoxRunDetails_create(BoxRunDetails_Config* config);
void BoxRunDetails_changeSelection(BoxRunDetails* instance, uint8_t selected);
void BoxRunDetails_setRun(BoxRunDetails* instance, Data_Run* run);
void BoxRunDetails_clearRun(BoxRunDetails* instance);

#endif