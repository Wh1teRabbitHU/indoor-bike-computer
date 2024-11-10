#include "list_run_details.h"

static uint8_t loadRuns                              = 0;
static uint8_t clearRuns                             = 1;
static uint32_t pageIndex                            = 0;
static uint32_t selectedIndex                        = 0;
static Data_Run runs[LIST_RUN_DETAILS_MAX_RUN_COUNT] = {0};

PRIVATE void ListRunDetails_loadRuns(ListRunDetails * instance) {
    LabelLoading_show(&instance->loadingLabel);

    Data_RunPage page = {.startIndex = pageIndex};
    Data_readRuns(&page);

    for (uint8_t i = 0; i < page.resultSize; i++) {
        Data_readRun(page.runs[i], &runs[page.resultSize - i - 1]);
    }

    clearRuns = 0;

    LabelLoading_hide(&instance->loadingLabel);
}

ListRunDetails ListRunDetails_create(ListRunDetails_Config * listConfig) {
    ListRunDetails runDetails = {};

    BoxRunsStatistics_Config statisticsConfig = {.screen = listConfig->screen, .x = 5, .y = 5};
    LabelPageHeader_Config pageHeaderConfig   = {.screen = listConfig->screen, .x = 5, .y = 102};
    LabelLoading_Config loadingLabelConfig    = {.screen = listConfig->screen, .bgColor = 0xEAEAEA};
    ModalRunDetails_Config modalConfig        = {.screen = listConfig->screen};

    runDetails.statistics      = BoxRunsStatistics_create(&statisticsConfig);
    runDetails.pageHeaderLabel = LabelPageHeader_create(&pageHeaderConfig);

    for (uint8_t i = 0; i < LIST_RUN_DETAILS_MAX_RUN_COUNT; i++) {
        int32_t x = 5, y = 148 + (i * (BOX_RUN_DETAILS_HEIGHT + BOX_RUN_DETAILS_MARGIN));
        BoxRunDetails_Config detailsConfig = {.screen = listConfig->screen, .x = x, .y = y};

        runDetails.boxes[i] = BoxRunDetails_create(&detailsConfig);
    }

    runDetails.loadingLabel = LabelLoading_create(&loadingLabelConfig);
    runDetails.modal        = ModalRunDetails_create(&modalConfig);

    return runDetails;
}

void ListRunDetails_init(ListRunDetails * instance) {
    Data_Statistics * statistics = Data_getStatistics();
    uint32_t maxRuns             = statistics->runs;

    pageIndex     = maxRuns - LIST_RUN_DETAILS_MAX_RUN_COUNT;
    selectedIndex = 0;
}

void ListRunDetails_triggerLoadRuns(ListRunDetails * instance) {
    loadRuns = 1;
}

void ListRunDetails_clearRuns() {
    clearRuns = 1;
}

void ListRunDetails_selectPrev(ListRunDetails * instance) {
    if (selectedIndex > 0) {
        selectedIndex--;

        return;
    }

    uint32_t endRunIndex = pageIndex + LIST_RUN_DETAILS_MAX_RUN_COUNT;
    uint32_t runCounts   = Data_countRuns();

    if (runCounts == 0 || endRunIndex > (runCounts - 1)) {
        return;
    }

    pageIndex++;
    loadRuns = 1;
}

void ListRunDetails_selectNext(ListRunDetails * instance) {
    if (selectedIndex < LIST_RUN_DETAILS_MAX_RUN_COUNT - 1) {
        selectedIndex++;

        return;
    }

    if (pageIndex == 0) {
        return;
    }

    pageIndex--;
    loadRuns = 1;
}

void ListRunDetails_execute(ListRunDetails * instance) {
    if (instance->modal.open) {
        ModalRunDetails_close(&instance->modal);
    } else {
        ModalRunDetails_open(&instance->modal);
    }
}

void ListRunDetails_stepOut(ListRunDetails * instance) {
    if (instance->modal.open) {
        ModalRunDetails_close(&instance->modal);
    }
}

void ListRunDetails_update(ListRunDetails * instance) {
    if (loadRuns) {
        // If the label is not marked as visible, we show it and only process the load in the next request, so the GUI
        // engine can draw the loading modal to the screen
        if (!instance->loadingLabel.visible) {
            LabelLoading_show(&instance->loadingLabel);

            return;
        }
        ListRunDetails_loadRuns(instance);

        loadRuns = 0;
    }

    BoxRunsStatistics_update(&instance->statistics, Data_getStatistics());

    for (uint8_t i = 0; i < LIST_RUN_DETAILS_MAX_RUN_COUNT; i++) {
        if (clearRuns) {
            BoxRunDetails_clearRun(&instance->boxes[i]);
        } else {
            BoxRunDetails_setRun(&instance->boxes[i], &runs[i]);
        }

        BoxRunDetails_changeSelection(&instance->boxes[i], i == selectedIndex);
    }

    uint32_t elementCount  = Data_getStatistics()->runs;
    uint32_t invertedIndex = elementCount - pageIndex - LIST_RUN_DETAILS_MAX_RUN_COUNT;

    instance->pageHeaderLabel.pageStart     = invertedIndex + 1;
    instance->pageHeaderLabel.pageEnd       = invertedIndex + LIST_RUN_DETAILS_MAX_RUN_COUNT;
    instance->pageHeaderLabel.selectedIndex = invertedIndex + selectedIndex + 1;
    instance->pageHeaderLabel.elementCount  = elementCount;

    LabelPageHeader_update(&instance->pageHeaderLabel);
    ModalRunDetails_update(&instance->modal, &runs[selectedIndex]);
    LabelLoading_hide(&instance->loadingLabel);
}