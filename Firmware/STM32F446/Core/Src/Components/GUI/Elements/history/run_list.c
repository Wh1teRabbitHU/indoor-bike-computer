#include "run_list.h"

static uint8_t boxesVisible               = 0; // If the value 1, the boxes are visible on the screen, otherwise it's hidden
static uint8_t loadRuns                   = 0; // This signals to the script to load the set run page. Runs are loaded in 2 tickts to be able to show the loading label
static uint32_t pageIndex                 = 0; // This defines the index of the run page, value should be between 0 and run counts - 1
static uint32_t boxIndex                  = 0; // This defines the currently selected box index, value should be between 0 and RUN_LIST_ITEM_COUNT - 1
static Data_Run runs[RUN_LIST_ITEM_COUNT] = {0};

PRIVATE void RunList_loadRuns(RunList * instance) {
    LoadingLabel_show(&instance->loadingLabel);

    Data_RunPage page = {.startIndex = pageIndex};
    Data_readRuns(&page);

    for (uint8_t i = 0; i < page.resultSize; i++) {
        Data_readRun(page.runs[i], &runs[page.resultSize - i - 1]);
    }

    LoadingLabel_hide(&instance->loadingLabel);
}

RunList RunList_create(RunList_Config * listConfig) {
    RunList runDetails = {};

    RunStatistics_Config statisticsConfig  = {.screen = listConfig->screen, .x = 5, .y = 5};
    PageHeader_Config pageHeaderConfig     = {.screen = listConfig->screen, .x = 5, .y = 102};
    LoadingLabel_Config loadingLabelConfig = {.screen = listConfig->screen, .bgColor = 0xEAEAEA};
    RunModal_Config modalConfig            = {.screen = listConfig->screen};

    runDetails.statistics = RunStatistics_create(&statisticsConfig);
    runDetails.pageHeader = PageHeader_create(&pageHeaderConfig);

    for (uint8_t i = 0; i < RUN_LIST_ITEM_COUNT; i++) {
        int32_t x = 5, y = 148 + (i * (RUN_LIST_ITEM_HEIGHT + RUN_LIST_ITEM_MARGIN));
        RunListItem_Config detailsConfig = {.screen = listConfig->screen, .x = x, .y = y};

        runDetails.items[i] = RunListItem_create(&detailsConfig);
    }

    runDetails.loadingLabel = LoadingLabel_create(&loadingLabelConfig);
    runDetails.modal        = RunModal_create(&modalConfig);

    return runDetails;
}

void RunList_init(RunList * instance) {
    Data_Statistics * statistics = Data_getStatistics();
    uint32_t maxRuns             = statistics->runs;

    pageIndex = RUN_LIST_ITEM_COUNT > maxRuns ? 0 : maxRuns - RUN_LIST_ITEM_COUNT;
    boxIndex  = 0;
}

void RunList_triggerLoadRuns(RunList * instance) {
    uint32_t runCounts = Data_countRuns();
    uint8_t pageSize   = RUN_LIST_ITEM_COUNT > runCounts ? runCounts : RUN_LIST_ITEM_COUNT;

    if (runCounts == 0) {
        return;
    }

    if (boxIndex > 0 && (boxIndex > pageSize - 1)) {
        boxIndex = pageSize - 1;
    }

    if (pageIndex > 0 && (pageIndex + pageSize > runCounts - 1)) {
        pageIndex = runCounts - pageSize - 1;
    }

    loadRuns     = 1;
    boxesVisible = 1;
}

void RunList_selectPrev(RunList * instance) {
    if (instance->modal.open) {
        RunModal_selectPrev(&instance->modal);
        return;
    }

    if (boxIndex > 0) {
        boxIndex--;

        return;
    }

    uint32_t endRunIndex = pageIndex + RUN_LIST_ITEM_COUNT;
    uint32_t runCounts   = Data_countRuns();

    if (runCounts == 0 || endRunIndex > (runCounts - 1)) {
        return;
    }

    pageIndex++;
    loadRuns = 1;
}

void RunList_selectNext(RunList * instance) {
    if (instance->modal.open) {
        RunModal_selectNext(&instance->modal);
        return;
    }

    uint32_t elementCount = Data_getStatistics()->runs;
    uint8_t pageSize      = RUN_LIST_ITEM_COUNT > elementCount ? elementCount : RUN_LIST_ITEM_COUNT;

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

void RunList_execute(RunList * instance) {
    if (instance->modal.open) {
        uint8_t refresh = RunModal_execute(&instance->modal);

        if (refresh) {
            RunList_triggerLoadRuns(instance);
        }
    } else {
        RunModal_open(&instance->modal);
    }
}

uint8_t RunList_stepOut(RunList * instance) {
    boxesVisible = 0;

    if (instance->modal.open) {
        return RunModal_stepOut(&instance->modal);
    }

    return 1;
}

void RunList_update(RunList * instance) {
    if (loadRuns) {
        // If the label is not marked as visible, we show it and only process the load in the next request, so the GUI
        // engine can draw the loading modal to the screen
        if (!instance->loadingLabel.visible) {
            LoadingLabel_show(&instance->loadingLabel);

            return;
        }
        RunList_loadRuns(instance);

        loadRuns = 0;
    }

    RunStatistics_update(&instance->statistics, Data_getStatistics());

    uint32_t elementCount = Data_getStatistics()->runs;
    uint8_t pageSize      = elementCount >= RUN_LIST_ITEM_COUNT ? RUN_LIST_ITEM_COUNT : elementCount;

    for (uint8_t i = 0; i < RUN_LIST_ITEM_COUNT; i++) {
        if (i > pageSize - 1) {
            RunListItem_hide(&instance->items[i]);

            continue;
        }

        RunListItem_setRun(&instance->items[i], &runs[i]);
        RunListItem_changeSelection(&instance->items[i], i == boxIndex);

        if (boxesVisible) {
            RunListItem_show(&instance->items[i]);
        } else {
            RunListItem_hide(&instance->items[i]);
        }
    }

    uint32_t invertedIndex = elementCount - pageIndex - pageSize;

    instance->pageHeader.pageStart     = elementCount == 0 ? 0 : invertedIndex + 1;
    instance->pageHeader.pageEnd       = invertedIndex + pageSize;
    instance->pageHeader.selectedIndex = elementCount == 0 ? 0 : invertedIndex + boxIndex + 1;
    instance->pageHeader.elementCount  = elementCount;

    PageHeader_update(&instance->pageHeader);
    RunModal_update(&instance->modal, &runs[boxIndex]);
    LoadingLabel_hide(&instance->loadingLabel);
}