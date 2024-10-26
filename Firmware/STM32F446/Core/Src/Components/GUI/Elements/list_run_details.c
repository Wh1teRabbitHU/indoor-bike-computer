#include "list_run_details.h"

static uint8_t clearRuns = 1;
static uint32_t currentRunIndex = 0;
static Data_Run runs[LIST_RUN_DETAILS_MAX_RUN_COUNT] = {0};

ListRunDetails ListRunDetails_create(ListRunDetails_Config* listConfig) {
    ListRunDetails runDetails = {};

    LabelLoading_Config loadingLabelConfig = {.screen = listConfig->screen, .bgColor = 0x77EEE6};

    runDetails.loadingLabel = LabelLoading_create(&loadingLabelConfig);

    for (uint8_t i = 0; i < LIST_RUN_DETAILS_MAX_RUN_COUNT; i++) {
        int32_t x = 5, y = 5 + (i * (BUX_RUN_DETAILS_HEIGHT + BUX_RUN_DETAILS_MARGIN));
        BoxRunDetails_Config config = {.screen = listConfig->screen, .x = x, .y = y};

        runDetails.boxes[i] = BoxRunDetails_create(&config);
    }

    return runDetails;
}

void ListRunDetails_loadRuns(ListRunDetails* instance) {
    LabelLoading_show(&instance->loadingLabel);

    Data_RunPage page = {.startIndex = currentRunIndex};
    Data_readRuns(&page);

    for (uint8_t i = 0; i < page.resultSize; i++) {
        Data_readRun(page.runs[i], &runs[i]);
    }

    clearRuns = 0;

    LabelLoading_hide(&instance->loadingLabel);
}

void ListRunDetails_clearRuns() { clearRuns = 1; }

void ListRunDetails_selectPrev(ListRunDetails* instance) {
    if (currentRunIndex == 0) {
        return;
    }

    currentRunIndex--;

    ListRunDetails_loadRuns(instance);
}

void ListRunDetails_selectNext(ListRunDetails* instance) {
    LabelLoading_show(&instance->loadingLabel);

    uint32_t endRunIndex = currentRunIndex + LIST_RUN_DETAILS_MAX_RUN_COUNT;
    uint32_t runCounts = Data_countRuns();

    if (runCounts == 0 || endRunIndex > (runCounts - 1)) {
        LabelLoading_hide(&instance->loadingLabel);
        return;
    }

    currentRunIndex++;

    ListRunDetails_loadRuns(instance);
}

void ListRunDetails_update(ListRunDetails* instance) {
    LabelLoading_update(&instance->loadingLabel);

    for (uint8_t i = 0; i < LIST_RUN_DETAILS_MAX_RUN_COUNT; i++) {
        if (clearRuns) {
            BoxRunDetails_clearRun(&instance->boxes[i]);
        } else {
            BoxRunDetails_setRun(&instance->boxes[i], &runs[i]);
        }
    }
}