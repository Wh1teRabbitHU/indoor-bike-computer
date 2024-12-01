#include "live_controls.h"

static const char * buttonMatrixMap[] = {"Start", "End", "Reset", ""};

PRIVATE void LiveControls_showButton(LiveControls * instance, uint8_t index) {
    lv_buttonmatrix_set_button_width(instance->buttonMatrix, index, 100);
    lv_buttonmatrix_clear_button_ctrl(instance->buttonMatrix, index, LV_BUTTONMATRIX_CTRL_HIDDEN);
}

PRIVATE void LiveControls_hideButton(LiveControls * instance, uint8_t index) {
    lv_buttonmatrix_set_button_width(instance->buttonMatrix, index, 0);
    lv_buttonmatrix_set_button_ctrl(instance->buttonMatrix, index, LV_BUTTONMATRIX_CTRL_HIDDEN);
}

LiveControls LiveControls_create(LiveControls_Config * config) {
    LiveControls controlInstance = {
        .selected = LIVE_CONTROLS_START, .enabled = {1, 0, 0}
    };

    lv_obj_t * buttonMatrix = lv_buttonmatrix_create(config->screen);

    lv_obj_align(buttonMatrix, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_set_width(buttonMatrix, 300);
    lv_obj_set_height(buttonMatrix, 50);
    lv_obj_set_pos(buttonMatrix, config->x, config->y);
    lv_obj_set_style_pad_all(buttonMatrix, 5, LV_PART_MAIN);
    lv_obj_remove_flag(buttonMatrix, LV_OBJ_FLAG_SCROLLABLE);

    lv_buttonmatrix_set_map(buttonMatrix, buttonMatrixMap);

    for (uint8_t i = 0; i < LIVE_CONTROLS_BUTTON_COUNT; i++) {
        lv_buttonmatrix_set_button_ctrl(buttonMatrix, i, LV_BUTTONMATRIX_CTRL_CHECKABLE);
    }

    controlInstance.buttonMatrix = buttonMatrix;

    LiveControls_updateState(&controlInstance);

    return controlInstance;
}

void LiveControls_updateState(LiveControls * instance) {
    for (uint8_t i = 0; i < LIVE_CONTROLS_BUTTON_COUNT; i++) {
        if (i == instance->selected) {
            lv_buttonmatrix_set_button_ctrl(instance->buttonMatrix, i, LV_BUTTONMATRIX_CTRL_CHECKED);
        } else {
            lv_buttonmatrix_clear_button_ctrl(instance->buttonMatrix, i, LV_BUTTONMATRIX_CTRL_CHECKED);
        }

        if (instance->enabled[i]) {
            lv_buttonmatrix_clear_button_ctrl(instance->buttonMatrix, i, LV_BUTTONMATRIX_CTRL_DISABLED);
        } else {
            lv_buttonmatrix_set_button_ctrl(instance->buttonMatrix, i, LV_BUTTONMATRIX_CTRL_DISABLED);
        }
    }
}

void LiveControls_updateBtnText(uint8_t index, char * text) {
    if (index >= LIVE_CONTROLS_BUTTON_COUNT) {
        return;
    }

    buttonMatrixMap[index] = text;
}
