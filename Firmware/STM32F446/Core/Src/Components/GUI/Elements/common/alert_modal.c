#include "alert_modal.h"

AlertModal AlertModal_create(AlertModal_Config * config) {
    AlertModal alertInstance = {};

    lv_obj_t * box = lv_obj_create(config->screen);

    lv_obj_align(box, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_set_width(box, ALERT_MODAL_WIDTH);
    lv_obj_set_height(box, ALERT_MODAL_HEIGHT);
    lv_obj_set_pos(box, ALERT_MODAL_POS_X, ALERT_MODAL_POS_Y);
    lv_obj_set_style_pad_all(box, 5, LV_PART_MAIN);
    lv_obj_remove_flag(box, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(box, ALERT_MODAL_DEFAULT_BG_COLOR, LV_PART_MAIN);

    lv_obj_t * title = lv_label_create(box);

    lv_obj_set_style_text_color(title, ALERT_MODAL_DEFAULT_FONT_COLOR, LV_PART_MAIN);
    lv_obj_align(title, LV_ALIGN_TOP_LEFT, 0, 10);
    lv_obj_set_width(title, ALERT_MODAL_WIDTH);
    lv_obj_set_height(title, 24);
    lv_obj_set_style_text_align(title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);

    lv_obj_t * body = lv_label_create(box);

    lv_obj_set_style_text_color(body, ALERT_MODAL_DEFAULT_FONT_COLOR, LV_PART_MAIN);
    lv_obj_align(body, LV_ALIGN_TOP_LEFT, ALERT_MODAL_BODY_PADDING, 45);
    lv_obj_set_width(body, ALERT_MODAL_WIDTH - ALERT_MODAL_BODY_PADDING);
    lv_obj_set_style_text_align(body, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);

    lv_obj_t * closeButton = lv_button_create(box);

    lv_obj_align(closeButton, LV_ALIGN_BOTTOM_LEFT, (ALERT_MODAL_WIDTH / 2) - (ALERT_MODAL_BTN_WIDTH / 2), 0);
    lv_obj_set_width(closeButton, ALERT_MODAL_BTN_WIDTH);
    lv_obj_set_height(closeButton, ALERT_MODAL_BTN_HEIGHT);
    lv_obj_set_style_bg_color(closeButton, lv_color_hex(0xAAAAAA), LV_PART_MAIN);
    lv_obj_set_style_border_color(closeButton, lv_color_hex(0x777777), LV_PART_MAIN);
    lv_obj_set_style_border_width(closeButton, 2, LV_PART_MAIN);
    lv_obj_t * closeButtonLabel = lv_label_create(closeButton);
    lv_label_set_text(closeButtonLabel, "Close");
    lv_obj_center(closeButtonLabel);

    alertInstance.variant     = ALERT_MODAL_VARIANT_DEFAULT;
    alertInstance.box         = box;
    alertInstance.title       = title;
    alertInstance.body        = body;
    alertInstance.closeButton = closeButton;

    AlertModal_hide(&alertInstance);

    return alertInstance;
}

void AlertModal_show(AlertModal * instance) {
    instance->visible = 1;
    instance->updated = 0;
}

void AlertModal_hide(AlertModal * instance) {
    if (!instance->closable) {
        return;
    }

    instance->visible = 0;
    instance->updated = 0;
}

void AlertModal_update(AlertModal * instance) {
    if (instance->updated) {
        return;
    }

    if (instance->visible) {
        lv_label_set_text(instance->title, instance->titleText);
        lv_label_set_text(instance->body, instance->bodyText);

        switch (instance->variant) {
        case ALERT_MODAL_VARIANT_DEFAULT:
            lv_obj_set_style_bg_color(instance->box, ALERT_MODAL_DEFAULT_BG_COLOR, LV_PART_MAIN);
            lv_obj_set_style_text_color(instance->title, ALERT_MODAL_DEFAULT_FONT_COLOR, LV_PART_MAIN);
            lv_obj_set_style_text_color(instance->body, ALERT_MODAL_DEFAULT_FONT_COLOR, LV_PART_MAIN);
            break;
        case ALERT_MODAL_VARIANT_INFO:
            lv_obj_set_style_bg_color(instance->box, ALERT_MODAL_INFO_BG_COLOR, LV_PART_MAIN);
            lv_obj_set_style_text_color(instance->title, ALERT_MODAL_INFO_FONT_COLOR, LV_PART_MAIN);
            lv_obj_set_style_text_color(instance->body, ALERT_MODAL_INFO_FONT_COLOR, LV_PART_MAIN);
            break;
        case ALERT_MODAL_VARIANT_WARNING:
            lv_obj_set_style_bg_color(instance->box, ALERT_MODAL_WARNING_BG_COLOR, LV_PART_MAIN);
            lv_obj_set_style_text_color(instance->title, ALERT_MODAL_WARNING_FONT_COLOR, LV_PART_MAIN);
            lv_obj_set_style_text_color(instance->body, ALERT_MODAL_WARNING_FONT_COLOR, LV_PART_MAIN);
            break;
        case ALERT_MODAL_VARIANT_ERROR:
            lv_obj_set_style_bg_color(instance->box, ALERT_MODAL_ERROR_BG_COLOR, LV_PART_MAIN);
            lv_obj_set_style_text_color(instance->title, ALERT_MODAL_ERROR_FONT_COLOR, LV_PART_MAIN);
            lv_obj_set_style_text_color(instance->body, ALERT_MODAL_ERROR_FONT_COLOR, LV_PART_MAIN);
            break;
        }

        if (instance->closable) {
            lv_obj_clear_flag(instance->closeButton, LV_OBJ_FLAG_HIDDEN);
        } else {
            lv_obj_add_flag(instance->closeButton, LV_OBJ_FLAG_HIDDEN);
        }

        lv_obj_clear_flag(instance->box, LV_OBJ_FLAG_HIDDEN);
    } else {
        lv_obj_add_flag(instance->box, LV_OBJ_FLAG_HIDDEN);
    }

    instance->updated = 1;
}