#include "main_tabview_live.h"

static MeasurementBoxDual difficultyBox;
static MeasurementBoxDual speedBox;
// static MeasurementBoxDual revolutionBox;
static MeasurementBoxSingle distanceBox;
static MeasurementBoxDual heartRateBox;
static MeasurementChart measurementChart;
static TimerBox timerBox;
static LiveControls controlLive;

PRIVATE void MainTabviewLive_executeStart() {
    if (State_Live_get()->sessionState == APP_LIVESTATE_SESSION_RUNNING) {
        return;
    }

    controlLive.enabled[LIVE_CONTROLS_END]   = 0;
    controlLive.enabled[LIVE_CONTROLS_RESET] = 0;

    LiveControls_updateBtnText(0, "Pause");

    State_Live_start();
    Stoptimer_start();
}

PRIVATE void MainTabviewLive_executePause() {
    State_Live_Session sessionState = State_Live_get()->sessionState;

    if (sessionState == APP_LIVESTATE_SESSION_PAUSED || sessionState == APP_LIVESTATE_SESSION_STOPPED) {
        return;
    }

    controlLive.enabled[LIVE_CONTROLS_END]   = 1;
    controlLive.enabled[LIVE_CONTROLS_RESET] = 1;

    LiveControls_updateBtnText(0, "Resume");

    Stoptimer_pause();
    State_Live_pause();
}

PRIVATE void MainTabviewLive_executeEnd() {
    // TODO: Confirm the decision with the user

    controlLive.selected                     = LIVE_CONTROLS_START;
    controlLive.enabled[LIVE_CONTROLS_END]   = 0;
    controlLive.enabled[LIVE_CONTROLS_RESET] = 0;

    LiveControls_updateBtnText(0, "Start");

    Data_Run * run = &State_Live_get()->liveRun;

    Stoptimer_stop();
    State_Live_stop();
    Data_addRunToStatistics(run);
}

PRIVATE void MainTabviewLive_executeReset() {
    // TODO: Confirm the decision with the user

    controlLive.selected                     = LIVE_CONTROLS_START;
    controlLive.enabled[LIVE_CONTROLS_END]   = 0;
    controlLive.enabled[LIVE_CONTROLS_RESET] = 0;

    LiveControls_updateBtnText(0, "Start");

    Data_Run * run = &State_Live_get()->liveRun;

    Stoptimer_stop();
    State_Live_stop();
    Data_deleteRun(run);
}

void MainTabviewLive_init(MainTabviewLive_Config * config) {
    MeasurementBox_Config difficultyBoxConfig = {
        .screen = config->tab, .title = "Difficulty", .x = 10, .y = 10, .bgColor = 0xBCC7FF};
    MeasurementBox_Config speedBoxConfig = {
        .screen = config->tab, .title = "Speed", .x = 165, .y = 10, .bgColor = 0x77EEE6};
    // MeasurementBox_Config revolutionBoxConfig = {
    //     .screen = config->tab, .title = "Revolution", .x = 10, .y = 120, .bgColor = 0xBFFFA1};
    MeasurementBox_Config distanceBoxConfig = {
        .screen = config->tab, .title = "Distance", .x = 10, .y = 120, .bgColor = 0xBFFFA1};
    MeasurementBox_Config heartRateBoxConfig = {
        .screen = config->tab, .title = "Heart Rate", .x = 165, .y = 120, .bgColor = 0xFFA490};
    MeasurementChart_Config measurementChartConfig = {.screen       = config->tab,
                                                      .title        = "Revolution",
                                                      .x            = 10,
                                                      .y            = 230,
                                                      .mainColor    = 0xE1F6FF,
                                                      .series1Color = 0x39B200};
    TimerBox_Config timerLabelConfig               = {
                      .screen = config->tab, .name = "Timer: ", .x = 10, .y = 368, .bgColor = 0xC993FF};
    LiveControls_Config controlLiveConfig = {.screen = config->tab, .x = 10, .y = 410, .bgColor = 0xEAEAEA};

    difficultyBox = MeasurementBox_createDual(&difficultyBoxConfig);
    speedBox      = MeasurementBox_createDual(&speedBoxConfig);
    // revolutionBox    = MeasurementBox_createDual(&revolutionBoxConfig);
    distanceBox      = MeasurementBox_createSingle(&distanceBoxConfig);
    heartRateBox     = MeasurementBox_createDual(&heartRateBoxConfig);
    measurementChart = MeasurementChart_create(&measurementChartConfig);
    timerBox         = TimerBox_create(&timerLabelConfig);
    controlLive      = LiveControls_create(&controlLiveConfig);
}

void MainTabviewLive_updateDifficulty(uint32_t current, uint32_t average) {
    char currentBuffer[16] = {0};
    char averageBuffer[16] = {0};

    sprintf(currentBuffer, "%ld\nmV", current);
    sprintf(averageBuffer, "%ld\nmV", DATA_AVG_CONVERT_VALUE(average));

    MeasurementBox_setDualValue(&difficultyBox, currentBuffer, averageBuffer);
}

void MainTabviewLive_updateSpeed(uint32_t current, uint32_t average) {
    char currentBuffer[16] = {0};
    char averageBuffer[16] = {0};

    uint8_t currentSpeedDecimal = current / 100;
    uint8_t averageSpeedDecimal = DATA_AVG_CONVERT_VALUE(average) / 100;

    sprintf(currentBuffer, "%d\nkmh", currentSpeedDecimal);
    sprintf(averageBuffer, "%d\nkmh", averageSpeedDecimal);

    MeasurementBox_setDualValue(&speedBox, currentBuffer, averageBuffer);
}

// void MainTabviewLive_updateRevolution(uint32_t current, uint32_t average) {
//     static char currentBuffer[16] = {0};
//     static char averageBuffer[16] = {0};

//     sprintf(currentBuffer, "%ld\nrpm", current);
//     sprintf(averageBuffer, "%ld\nrpm", DATA_AVG_CONVERT_VALUE(average));

//     MeasurementBox_setDualValue(&revolutionBox, currentBuffer, averageBuffer);
// }

void MainTabviewLive_updateDistance(uint32_t distance) {
    char distanceBuffer[16] = {0};

    sprintf(distanceBuffer, "%ldm", distance / 100);

    MeasurementBox_setSingleValue(&distanceBox, distanceBuffer);
}

void MainTabviewLive_updateHeartRate(uint32_t current, uint32_t average) {
    char currentBuffer[16] = {0};
    char averageBuffer[16] = {0};

    sprintf(currentBuffer, "%ld\nbpm", current);
    sprintf(averageBuffer, "%ld\nbpm", DATA_AVG_CONVERT_VALUE(average));

    MeasurementBox_setDualValue(&heartRateBox, currentBuffer, averageBuffer);
}

void MainTabviewLive_updateChart(uint8_t updateChart) {
    if (!updateChart) {
        return;
    }

    // TODO: Replace with a proper implementation
    MeasurementChart_setValue(&measurementChart, lv_rand(75, 85));
}

void MainTabviewLive_updateTimer(char * time) {
    TimerBox_setValue(&timerBox, time);
}

void MainTabviewLive_updateControl(void) {
    LiveControls_updateState(&controlLive);
}

void MainTabviewLive_stepIn() {
    // Do nothing
}
void MainTabviewLive_stepOut() {
    // Do nothing
}

void MainTabviewLive_execute(void) {
    switch (controlLive.selected) {
    case LIVE_CONTROLS_START:
        if (State_Live_get()->sessionState == APP_LIVESTATE_SESSION_RUNNING) {
            MainTabviewLive_executePause();
        } else {
            MainTabviewLive_executeStart();
        }
        break;
    case LIVE_CONTROLS_END:
        MainTabviewLive_executeEnd();
        break;
    case LIVE_CONTROLS_RESET:
        MainTabviewLive_executeReset();
        break;
    }
}

void MainTabviewLive_handlePrev(void) {
    uint32_t current = controlLive.selected;

    do {
        if (current == 0) {
            current = LIVE_CONTROLS_BUTTON_COUNT - 1;
        } else {
            current--;
        }

        if (current == controlLive.selected) {
            break;
        }
    } while (!controlLive.enabled[current]);

    controlLive.selected = current;
}

void MainTabviewLive_handleNext(void) {
    uint32_t current = controlLive.selected;

    do {
        if (current == (LIVE_CONTROLS_BUTTON_COUNT - 1)) {
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
