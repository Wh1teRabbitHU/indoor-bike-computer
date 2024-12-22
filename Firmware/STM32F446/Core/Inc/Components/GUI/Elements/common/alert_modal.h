#ifndef __ALERT_MODAL_H_
#define __ALERT_MODAL_H_

#include "er_tft035.h"
#include "lvgl.h"

#define ALERT_MODAL_WIDTH              300
#define ALERT_MODAL_HEIGHT             200
#define ALERT_MODAL_BTN_WIDTH          150
#define ALERT_MODAL_BTN_HEIGHT         30
#define ALERT_MODAL_POS_X              (ER_TFT035_SCREEN_WIDTH / 2) - (ALERT_MODAL_WIDTH / 2)
#define ALERT_MODAL_POS_Y              (ER_TFT035_SCREEN_HEIGHT / 2) - (ALERT_MODAL_HEIGHT / 2)
#define ALERT_MODAL_BODY_PADDING       10
#define ALERT_MODAL_DEFAULT_BG_COLOR   lv_color_hex(0xFFFFFF)
#define ALERT_MODAL_DEFAULT_FONT_COLOR lv_color_hex(0x000000)
#define ALERT_MODAL_INFO_BG_COLOR      lv_color_hex(0x0000AA)
#define ALERT_MODAL_INFO_FONT_COLOR    lv_color_hex(0xFFFFFF)
#define ALERT_MODAL_WARNING_BG_COLOR   lv_color_hex(0xAAAA00)
#define ALERT_MODAL_WARNING_FONT_COLOR lv_color_hex(0xFFFFFF)
#define ALERT_MODAL_ERROR_BG_COLOR     lv_color_hex(0xAA0000)
#define ALERT_MODAL_ERROR_FONT_COLOR   lv_color_hex(0xFFFFFF)

typedef enum AlertModal_Variant_t {
    ALERT_MODAL_VARIANT_DEFAULT = 0,
    ALERT_MODAL_VARIANT_INFO    = 1,
    ALERT_MODAL_VARIANT_WARNING = 2,
    ALERT_MODAL_VARIANT_ERROR   = 3,
} AlertModal_Variant_t;

typedef struct AlertModal {
    lv_obj_t * box;
    lv_obj_t * title;
    lv_obj_t * body;
    lv_obj_t * closeButton;
    AlertModal_Variant_t variant;
    uint8_t closable;
    uint8_t visible;
    uint8_t updated;
    char titleText[32];
    char bodyText[128];
} AlertModal;

typedef struct AlertModal_Config {
    lv_obj_t * screen;
} AlertModal_Config;

AlertModal AlertModal_create(AlertModal_Config * config);
void AlertModal_show(AlertModal * instance);
void AlertModal_hide(AlertModal * instance);
void AlertModal_update(AlertModal * instance);

#endif