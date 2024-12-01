#include "main_tabview_history.h"

static RunList runDetails;

void MainTabviewHistory_init(MainTabviewHistory_Config * config) {
    RunList_Config runDetailsConfig = {.screen = config->tab};

    runDetails = RunList_create(&runDetailsConfig);
}

void MainTabviewHistory_stepIn(void) {
    RunList_init(&runDetails);
    RunList_triggerLoadRuns(&runDetails);
}

void MainTabviewHistory_execute(void) {
    RunList_execute(&runDetails);
}

uint8_t MainTabviewHistory_stepOut() {
    return RunList_stepOut(&runDetails);
}

void MainTabviewHistory_handlePrev(void) {
    RunList_selectPrev(&runDetails);
}

void MainTabviewHistory_handleNext(void) {
    RunList_selectNext(&runDetails);
}

void MainTabviewHistory_update(void) {
    RunList_update(&runDetails);
}
