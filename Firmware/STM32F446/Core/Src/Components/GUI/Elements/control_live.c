#include "control_live.h"

static const char* buttonMatrixMap[] = {"Start", "End", "Reset", ""};

PRIVATE void ControlLive_showButton(ControlLive* instance, uint8_t index) {
    lv_buttonmatrix_set_button_width(instance->buttonMatrix, index, 100);
    lv_buttonmatrix_clear_button_ctrl(instance->buttonMatrix, index, LV_BUTTONMATRIX_CTRL_HIDDEN);
}

PRIVATE void ControlLive_hideButton(ControlLive* instance, uint8_t index) {
    lv_buttonmatrix_set_button_width(instance->buttonMatrix, index, 0);
    lv_buttonmatrix_set_button_ctrl(instance->buttonMatrix, index, LV_BUTTONMATRIX_CTRL_HIDDEN);
}

ControlLive ControlLive_create(ControlLive_Config* config) {
    ControlLive controlInstance = {.selected = CONTROLLIVE_START, .enabled = {1, 0, 0}};

    lv_obj_t* buttonMatrix = lv_buttonmatrix_create(config->screen);

    lv_obj_align(buttonMatrix, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_set_width(buttonMatrix, 300);
    lv_obj_set_height(buttonMatrix, 50);
    lv_obj_set_pos(buttonMatrix, config->x, config->y);
    lv_obj_set_style_pad_all(buttonMatrix, 5, LV_PART_MAIN);
    lv_obj_remove_flag(buttonMatrix, LV_OBJ_FLAG_SCROLLABLE);

    lv_buttonmatrix_set_map(buttonMatrix, buttonMatrixMap);

    for (uint8_t i = 0; i < CONTROLLIVE_BUTTON_COUNT; i++) {
        lv_buttonmatrix_set_button_ctrl(buttonMatrix, i, LV_BUTTONMATRIX_CTRL_CHECKABLE);
    }

    controlInstance.buttonMatrix = buttonMatrix;

    ControlLive_updateState(&controlInstance);

    return controlInstance;
}

void ControlLive_updateState(ControlLive* instance) {
    for (uint8_t i = 0; i < CONTROLLIVE_BUTTON_COUNT; i++) {
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

void ControlLive_updateBtnText(uint8_t index, char* text) {
    if (index >= CONTROLLIVE_BUTTON_COUNT) {
        return;
    }

    buttonMatrixMap[index] = text;
}
