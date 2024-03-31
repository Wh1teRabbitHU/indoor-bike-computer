#include "control_live.h"

static const char* buttonMatrixMap[] = {"Start", "End", "Reset", ""};

PRIVATE void ControlLive_updateSelected(ControlLive* controlInstance) {
    for (uint8_t i = 0; i < CONTROLLIVE_BUTTON_COUNT; i++) {
        if (i == controlInstance->selected) {
            lv_buttonmatrix_set_button_ctrl(controlInstance->buttonMatrix, i, LV_BUTTONMATRIX_CTRL_CHECKED);
        } else {
            lv_buttonmatrix_clear_button_ctrl(controlInstance->buttonMatrix, i, LV_BUTTONMATRIX_CTRL_CHECKED);
        }
    }
}

PRIVATE void ControlLive_updateEnabledState(ControlLive* controlInstance) {
    for (uint8_t i = 0; i < CONTROLLIVE_BUTTON_COUNT; i++) {
        if (controlInstance->enabled[i]) {
            lv_buttonmatrix_clear_button_ctrl(controlInstance->buttonMatrix, i, LV_BUTTONMATRIX_CTRL_DISABLED);
        } else {
            lv_buttonmatrix_set_button_ctrl(controlInstance->buttonMatrix, i, LV_BUTTONMATRIX_CTRL_DISABLED);
        }
    }
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
    lv_buttonmatrix_set_button_ctrl(buttonMatrix, 0, LV_BUTTONMATRIX_CTRL_CHECKABLE);
    lv_buttonmatrix_set_button_ctrl(buttonMatrix, 1, LV_BUTTONMATRIX_CTRL_CHECKABLE);
    lv_buttonmatrix_set_button_ctrl(buttonMatrix, 2, LV_BUTTONMATRIX_CTRL_CHECKABLE);

    controlInstance.buttonMatrix = buttonMatrix;

    ControlLive_updateSelected(&controlInstance);
    ControlLive_updateEnabledState(&controlInstance);

    return controlInstance;
}

void ControlLive_updateState(ControlLive* instance) {
    ControlLive_updateSelected(instance);
    ControlLive_updateEnabledState(instance);
}