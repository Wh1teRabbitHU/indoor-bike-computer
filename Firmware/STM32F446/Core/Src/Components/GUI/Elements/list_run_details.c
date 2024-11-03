#include "list_run_details.h"

static uint8_t clearRuns = 1;
static uint32_t pageIndex = 0;
static uint32_t selectedIndex = 0;
static Data_Run runs[LIST_RUN_DETAILS_MAX_RUN_COUNT] = {0};

ListRunDetails ListRunDetails_create(ListRunDetails_Config* listConfig) {
    ListRunDetails runDetails = {};

    BoxRunsStatistics_Config statisticsConfig = {.screen = listConfig->screen, .x = 5, .y = 5};
    LabelPageHeader_Config pageHeaderConfig = {.screen = listConfig->screen, .x = 5, .y = 102};
    LabelLoading_Config loadingLabelConfig = {.screen = listConfig->screen, .bgColor = 0x77EEE6};

    runDetails.statistics = BoxRunsStatistics_create(&statisticsConfig);
    runDetails.pageHeaderLabel = LabelPageHeader_create(&pageHeaderConfig);

    for (uint8_t i = 0; i < LIST_RUN_DETAILS_MAX_RUN_COUNT; i++) {
        int32_t x = 5, y = 148 + (i * (BOX_RUN_DETAILS_HEIGHT + BOX_RUN_DETAILS_MARGIN));
        BoxRunDetails_Config detailsConfig = {.screen = listConfig->screen, .x = x, .y = y};

        runDetails.boxes[i] = BoxRunDetails_create(&detailsConfig);
    }

    runDetails.loadingLabel = LabelLoading_create(&loadingLabelConfig);

    return runDetails;
}

void ListRunDetails_init(ListRunDetails* instance) {
    Data_Statistics* statistics = Data_getStatistics();
    uint32_t maxRuns = statistics->runs;

    pageIndex = maxRuns - LIST_RUN_DETAILS_MAX_RUN_COUNT;
    selectedIndex = 0;
}

void ListRunDetails_loadRuns(ListRunDetails* instance) {
    LabelLoading_show(&instance->loadingLabel);

    Data_RunPage page = {.startIndex = pageIndex};
    Data_readRuns(&page);

    for (uint8_t i = 0; i < page.resultSize; i++) {
        Data_readRun(page.runs[i], &runs[page.resultSize - i - 1]);
    }

    clearRuns = 0;

    LabelLoading_hide(&instance->loadingLabel);
}

void ListRunDetails_clearRuns() { clearRuns = 1; }

void ListRunDetails_selectPrev(ListRunDetails* instance) {
    if (selectedIndex > 0) {
        selectedIndex--;

        return;
    }

    LabelLoading_show(&instance->loadingLabel);

    uint32_t endRunIndex = pageIndex + LIST_RUN_DETAILS_MAX_RUN_COUNT;
    uint32_t runCounts = Data_countRuns();

    if (runCounts == 0 || endRunIndex > (runCounts - 1)) {
        LabelLoading_hide(&instance->loadingLabel);
        return;
    }

    pageIndex++;

    ListRunDetails_loadRuns(instance);
}

void ListRunDetails_selectNext(ListRunDetails* instance) {
    if (selectedIndex < LIST_RUN_DETAILS_MAX_RUN_COUNT - 1) {
        selectedIndex++;

        return;
    }

    if (pageIndex == 0) {
        return;
    }

    pageIndex--;

    ListRunDetails_loadRuns(instance);
}

void ListRunDetails_update(ListRunDetails* instance) {
    LabelLoading_update(&instance->loadingLabel);
    BoxRunsStatistics_update(&instance->statistics, Data_getStatistics());

    for (uint8_t i = 0; i < LIST_RUN_DETAILS_MAX_RUN_COUNT; i++) {
        if (clearRuns) {
            BoxRunDetails_clearRun(&instance->boxes[i]);
        } else {
            BoxRunDetails_setRun(&instance->boxes[i], &runs[i]);
        }

        BoxRunDetails_changeSelection(&instance->boxes[i], i == selectedIndex);
    }

    uint32_t elementCount = Data_getStatistics()->runs;
    uint32_t invertedIndex = elementCount - pageIndex - LIST_RUN_DETAILS_MAX_RUN_COUNT;

    instance->pageHeaderLabel.pageStart = invertedIndex + 1;
    instance->pageHeaderLabel.pageEnd = invertedIndex + LIST_RUN_DETAILS_MAX_RUN_COUNT;
    instance->pageHeaderLabel.selectedIndex = invertedIndex + selectedIndex + 1;
    instance->pageHeaderLabel.elementCount = elementCount;

    LabelPageHeader_update(&instance->pageHeaderLabel);
}