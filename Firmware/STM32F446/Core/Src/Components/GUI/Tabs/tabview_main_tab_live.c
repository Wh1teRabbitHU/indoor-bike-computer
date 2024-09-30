#include "tabview_main_tab_live.h"

static BoxMeasurement difficultyBox;
static BoxMeasurement speedBox;
static BoxMeasurement revolutionBox;
static BoxMeasurement heartRateBox;
static ChartMeasurement measurementChart;
static LabelTimer timerLabel;
static ControlLive controlLive;

static char textBuffer[32] = {0};

PRIVATE void TabView_Main_Tab_Live_executeStart() {
    if (State_Live_get()->sessionState == APP_LIVESTATE_SESSION_RUNNING) {
        return;
    }

    controlLive.enabled[CONTROLLIVE_END] = 0;
    controlLive.enabled[CONTROLLIVE_RESET] = 0;

    ControlLive_updateBtnText(0, "Pause");

    State_Live_start();
    Stoptimer_start();
}

PRIVATE void TabView_Main_Tab_Live_executePause() {
    State_Live_Session sessionState = State_Live_get()->sessionState;

    if (sessionState == APP_LIVESTATE_SESSION_PAUSED || sessionState == APP_LIVESTATE_SESSION_STOPPED) {
        return;
    }

    controlLive.enabled[CONTROLLIVE_END] = 1;
    controlLive.enabled[CONTROLLIVE_RESET] = 1;

    ControlLive_updateBtnText(0, "Start");

    Stoptimer_pause();
    State_Live_pause();
}

PRIVATE void TabView_Main_Tab_Live_executeEnd() {
    Stoptimer_stop();
    State_Live_stop();
    // TODO: Handle finishing the current session:
    // TODO: Confirm the decision with the user
    // TODO: Reset state - Done
    // TODO: Update screen? - Done
}

PRIVATE void TabView_Main_Tab_Live_executeReset() {
    Stoptimer_stop();
    State_Live_stop();
    // TODO: Handle reseting the current session:
    // TODO: Confirm the decision with the user
    // TODO: Reset state - Done
    // TODO: Update screen? - Done
}

void TabView_Main_Tab_Live_init(TabView_Main_Tab_Live_Config* config) {
    BoxMeasurement_Config difficultyBoxConfig = {
        .screen = config->tab, .title = "Difficulty", .x = 10, .y = 10, .bgColor = 0xBCC7FF};
    BoxMeasurement_Config speedBoxConfig = {
        .screen = config->tab, .title = "Speed", .x = 165, .y = 10, .bgColor = 0x77EEE6};
    BoxMeasurement_Config revolutionBoxConfig = {
        .screen = config->tab, .title = "Revolution", .x = 10, .y = 120, .bgColor = 0xBFFFA1};
    BoxMeasurement_Config heartRateBoxConfig = {
        .screen = config->tab, .title = "Heart Rate", .x = 165, .y = 120, .bgColor = 0xFFA490};
    ChartMeasurement_Config measurementChartConfig = {.screen = config->tab,
                                                      .title = "Revolution",
                                                      .x = 10,
                                                      .y = 230,
                                                      .mainColor = 0xE1F6FF,
                                                      .series1Color = 0x39B200};
    LabelTimer_Config timerLabelConfig = {
        .screen = config->tab, .name = "Timer: ", .x = 10, .y = 368, .bgColor = 0xC993FF};
    ControlLive_Config controlLiveConfig = {.screen = config->tab, .x = 10, .y = 410, .bgColor = 0xEAEAEA};

    difficultyBox = BoxMeasurement_create(&difficultyBoxConfig);
    speedBox = BoxMeasurement_create(&speedBoxConfig);
    revolutionBox = BoxMeasurement_create(&revolutionBoxConfig);
    heartRateBox = BoxMeasurement_create(&heartRateBoxConfig);
    measurementChart = ChartMeasurement_create(&measurementChartConfig);
    timerLabel = LabelTimer_create(&timerLabelConfig);
    controlLive = ControlLive_create(&controlLiveConfig);
}

void TabView_Main_Tab_Live_updateDifficulty(uint32_t difficulty) {
    sprintf(textBuffer, "%ld\nmV", difficulty);

    BoxMeasurement_setValue(&difficultyBox, textBuffer, textBuffer);
}

void TabView_Main_Tab_Live_updateSpeed(uint32_t speed) {
    uint8_t speedDecimal = speed / 100;

    sprintf(textBuffer, "%d\nkmh", speedDecimal);

    BoxMeasurement_setValue(&speedBox, textBuffer, textBuffer);
}

void TabView_Main_Tab_Live_updateRevolution(uint32_t rpm) {
    sprintf(textBuffer, "%ld\nrpm", rpm);

    BoxMeasurement_setValue(&revolutionBox, textBuffer, textBuffer);
}

void TabView_Main_Tab_Live_updateHeartRate(uint32_t bpm) {
    sprintf(textBuffer, "%ld\nbpm", bpm);

    BoxMeasurement_setValue(&heartRateBox, textBuffer, textBuffer);
}

void TabView_Main_Tab_Live_updateChart(uint8_t updateChart) {
    if (!updateChart) {
        return;
    }

    // TODO: Replace with a proper implementation
    ChartMeasurement_setValue(&measurementChart, lv_rand(75, 85));
}

void TabView_Main_Tab_Live_updateTimer(char* time) { LabelTimer_setValue(&timerLabel, time); }

void TabView_Main_Tab_Live_updateControl(void) { ControlLive_updateState(&controlLive); }

void TabView_Main_Tab_Live_stepIn() {}
void TabView_Main_Tab_Live_stepOut() {}

// Control handlers
void TabView_Main_Tab_Live_execute(void) {
    switch (controlLive.selected) {
        case CONTROLLIVE_START:
            if (State_Live_get()->sessionState == APP_LIVESTATE_SESSION_RUNNING) {
                TabView_Main_Tab_Live_executePause();
            } else {
                TabView_Main_Tab_Live_executeStart();
            }
            break;
        case CONTROLLIVE_END:
            TabView_Main_Tab_Live_executeEnd();
            break;
        case CONTROLLIVE_RESET:
            TabView_Main_Tab_Live_executeReset();
            break;
    }
}

void TabView_Main_Tab_Live_handlePrev(void) {
    uint32_t current = controlLive.selected;

    do {
        if (current == 0) {
            current = CONTROLLIVE_BUTTON_COUNT - 1;
        } else {
            current--;
        }

        if (current == controlLive.selected) {
            break;
        }
    } while (!controlLive.enabled[current]);

    controlLive.selected = current;
}

void TabView_Main_Tab_Live_handleNext(void) {
    uint32_t current = controlLive.selected;

    do {
        if (current == (CONTROLLIVE_BUTTON_COUNT - 1)) {
            current = 0;
        } else {
            current++;
        }

        if (current == controlLive.selected) {
            break;
        }
    } while (!controlLive.enabled[current]);

    controlLive.selected = current;
}
