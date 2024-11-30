#include "list_run_details.h"

static uint8_t boxesVisible                      = 0; // If the value 1, the boxes are visible on the screen, otherwise it's hidden
static uint8_t loadRuns                          = 0; // This signals to the script to load the set run page. Runs are loaded in 2 tickts to be able to show the loading label
static uint32_t pageIndex                        = 0; // This defines the index of the run page, value should be between 0 and run counts - 1
static uint32_t boxIndex                         = 0; // This defines the currently selected box index, value should be between 0 and LIST_RUN_DETAILS_BOX_COUNT - 1
static Data_Run runs[LIST_RUN_DETAILS_BOX_COUNT] = {0};

PRIVATE void ListRunDetails_loadRuns(ListRunDetails * instance) {
    LabelLoading_show(&instance->loadingLabel);

    Data_RunPage page = {.startIndex = pageIndex};
    Data_readRuns(&page);

    for (uint8_t i = 0; i < page.resultSize; i++) {
        Data_readRun(page.runs[i], &runs[page.resultSize - i - 1]);
    }

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

    for (uint8_t i = 0; i < LIST_RUN_DETAILS_BOX_COUNT; i++) {
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

    pageIndex = LIST_RUN_DETAILS_BOX_COUNT > maxRuns ? 0 : maxRuns - LIST_RUN_DETAILS_BOX_COUNT;
    boxIndex  = 0;
}

void ListRunDetails_triggerLoadRuns(ListRunDetails * instance) {
    uint32_t runCounts = Data_countRuns();
    uint8_t pageSize   = LIST_RUN_DETAILS_BOX_COUNT > runCounts ? runCounts : LIST_RUN_DETAILS_BOX_COUNT;

    if (boxIndex > 0 && (boxIndex > pageSize - 1)) {
        boxIndex = pageSize - 1;
    }

    if (pageIndex > 0 && (pageIndex + pageSize > runCounts - 1)) {
        pageIndex = runCounts - pageSize - 1;
    }

    loadRuns     = 1;
    boxesVisible = 1;
}

void ListRunDetails_selectPrev(ListRunDetails * instance) {
    if (instance->modal.open) {
        ModalRunDetails_selectPrev(&instance->modal);
        return;
    }

    if (boxIndex > 0) {
        boxIndex--;

        return;
    }

    uint32_t endRunIndex = pageIndex + LIST_RUN_DETAILS_BOX_COUNT;
    uint32_t runCounts   = Data_countRuns();

    if (runCounts == 0 || endRunIndex > (runCounts - 1)) {
        return;
    }

    pageIndex++;
    loadRuns = 1;
}

void ListRunDetails_selectNext(ListRunDetails * instance) {
    if (instance->modal.open) {
        ModalRunDetails_selectNext(&instance->modal);
        return;
    }

    uint32_t elementCount = Data_getStatistics()->runs;
    uint8_t pageSize      = LIST_RUN_DETAILS_BOX_COUNT > elementCount ? elementCount : LIST_RUN_DETAILS_BOX_COUNT;

    if (boxIndex < pageSize - 1) {
        boxIndex++;

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
        uint8_t refresh = ModalRunDetails_execute(&instance->modal);

        if (refresh) {
            ListRunDetails_triggerLoadRuns(instance);
        }
    } else {
        ModalRunDetails_open(&instance->modal);
    }
}

uint8_t ListRunDetails_stepOut(ListRunDetails * instance) {
    boxesVisible = 0;

    if (instance->modal.open) {
        return ModalRunDetails_stepOut(&instance->modal);
    }

    return 1;
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

    uint32_t elementCount = Data_getStatistics()->runs;
    uint8_t pageSize      = elementCount >= LIST_RUN_DETAILS_BOX_COUNT ? LIST_RUN_DETAILS_BOX_COUNT : elementCount;

    for (uint8_t i = 0; i < LIST_RUN_DETAILS_BOX_COUNT; i++) {
        if (i > pageSize - 1) {
            BoxRunDetails_hide(&instance->boxes[i]);

            continue;
        }

        BoxRunDetails_setRun(&instance->boxes[i], &runs[i]);
        BoxRunDetails_changeSelection(&instance->boxes[i], i == boxIndex);

        if (boxesVisible) {
            BoxRunDetails_show(&instance->boxes[i]);
        } else {
            BoxRunDetails_hide(&instance->boxes[i]);
        }
    }

    uint32_t invertedIndex = elementCount - pageIndex - pageSize;

    instance->pageHeaderLabel.pageStart     = invertedIndex + 1;
    instance->pageHeaderLabel.pageEnd       = invertedIndex + pageSize;
    instance->pageHeaderLabel.selectedIndex = invertedIndex + boxIndex + 1;
    instance->pageHeaderLabel.elementCount  = elementCount;

    LabelPageHeader_update(&instance->pageHeaderLabel);
    ModalRunDetails_update(&instance->modal, &runs[boxIndex]);
    LabelLoading_hide(&instance->loadingLabel);
}