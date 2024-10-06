#include "list_run_details.h"

static uint32_t currentRunIndex = 0;

ListRunDetails ListRunDetails_create(ListRunDetails_Config* listConfig) {
    ListRunDetails runDetails = {};

    LabelLoading_Config loadingLabelConfig = {.screen = listConfig->screen, .bgColor = 0x77EEE6};

    runDetails.loadingLabel = LabelLoading_create(&loadingLabelConfig);

    for (uint8_t i = 0; i < LIST_RUN_DETAILS_MAX_RUN_COUNT; i++) {
        BoxRunDetails_Config config = {.screen = listConfig->screen, .x = 5, .y = 5 + (i * 100)};

        runDetails.boxes[i] = BoxRunDetails_create(&config);
    }

    return runDetails;
}

void ListRunDetails_loadRuns(ListRunDetails* instance) {
    LabelLoading_show(&instance->loadingLabel);

    Data_RunPage page = {.startIndex = currentRunIndex};
    Data_readRuns(&page);

    for (uint8_t i = 0; i < page.resultSize; i++) {
        Data_Run run = {0};

        Data_readRun(page.runs[i], &run);
        BoxRunDetails_setRun(&instance->boxes[i], &run);
    }

    LabelLoading_hide(&instance->loadingLabel);
}

void ListRunDetails_clearRuns(ListRunDetails* instance) {
    LabelLoading_show(&instance->loadingLabel);

    for (uint8_t i = 0; i < LIST_RUN_DETAILS_MAX_RUN_COUNT; i++) {
        BoxRunDetails_clearRun(&instance->boxes[i]);
    }

    LabelLoading_hide(&instance->loadingLabel);
}

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

    if (runCounts == 0 || endRunIndex >= (runCounts - 1)) {
        return;
    }

    currentRunIndex++;

    ListRunDetails_loadRuns(instance);
}