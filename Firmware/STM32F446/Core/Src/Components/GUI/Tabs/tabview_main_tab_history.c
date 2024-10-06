#include "tabview_main_tab_history.h"

static ListRunDetails runDetails;

void TabView_Main_Tab_History_init(TabView_Main_Tab_History_Config* config) {
    ListRunDetails_Config runDetailsConfig = {.screen = config->tab};

    runDetails = ListRunDetails_create(&runDetailsConfig);
}

void TabView_Main_Tab_History_stepIn(void) { ListRunDetails_loadRuns(&runDetails); }

void TabView_Main_Tab_History_stepOut(void) { ListRunDetails_clearRuns(&runDetails); }

void TabView_Main_Tab_History_execute(void) {
    // Do nothing
}

void TabView_Main_Tab_History_handlePrev(void) { ListRunDetails_selectPrev(&runDetails); }

void TabView_Main_Tab_History_handleNext(void) { ListRunDetails_selectNext(&runDetails); }
