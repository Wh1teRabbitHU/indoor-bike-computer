#include "state.h"

static State_Global global = {.infoMessage = NULL, .errorMessage = NULL, .updateLevel = 0};
static State_Live live     = {.difficulty   = 0,
                              .speed        = 0,
                              .rpm          = 0,
                              .bpm          = 0,
                              .updateChart  = 0,
                              .sessionState = APP_LIVESTATE_SESSION_STOPPED,
                              .running      = 0};

State_Global * State_getGlobal(void) {
    return &global;
}

State_Live * State_getLive(void) {
    return &live;
}

void State_startRun() {
    if (!live.running) {
        Data_Run run                    = {0};
        Data_RunMeasurement measurement = {0};

        Data_initRun(&run);

        live.running         = 1;
        live.liveRun         = run;
        live.lastMeasurement = measurement;
    }

    live.sessionState = APP_LIVESTATE_SESSION_RUNNING;
}

void State_pauseRun() {
    State_getLive()->sessionState = APP_LIVESTATE_SESSION_PAUSED;
}

void State_updateRun(char * timestamp) {
    live.time        = timestamp;
    live.updateChart = 1;
    live.haltCounter += 1;

    if (live.haltCounter > STATE_SIGNAL_TIMEOUT_THRESHOLD) {
        live.pedalRotating = 0;
    }

    live.lastMeasurement.timestamp += 1; // Add one second
    live.lastMeasurement.bpm        = live.bpm;
    live.lastMeasurement.difficulty = live.difficulty;
    live.lastMeasurement.rpm        = live.pedalRotating ? live.rpm : 0;
    live.lastMeasurement.speed      = live.pedalRotating ? live.speed : 0;

    live.liveRun.sessionLength += 1; // Add one second
    live.liveRun.distance += BIKE_CALCULATE_DISTANCE(live.speed);

    if (live.liveRun.sessionLength == 1) {
        live.liveRun.avgBpm        = DATA_CALCULATE_AVG(live.bpm, 0, 0);
        live.liveRun.avgSpeed      = DATA_CALCULATE_AVG(live.speed, 0, 0);
        live.liveRun.avgRpm        = DATA_CALCULATE_AVG(live.rpm, 0, 0);
        live.liveRun.avgDifficulty = DATA_CALCULATE_AVG(live.difficulty, 0, 0);
    } else {
        uint32_t avgCount = live.liveRun.sessionLength - 1;

        live.liveRun.avgBpm        = DATA_CALCULATE_AVG(live.bpm, live.liveRun.avgBpm, avgCount);
        live.liveRun.avgSpeed      = DATA_CALCULATE_AVG(live.speed, live.liveRun.avgSpeed, avgCount);
        live.liveRun.avgRpm        = DATA_CALCULATE_AVG(live.rpm, live.liveRun.avgRpm, avgCount);
        live.liveRun.avgDifficulty = DATA_CALCULATE_AVG(live.difficulty, live.liveRun.avgDifficulty, avgCount);
    }

    Data_storeRun(&live.liveRun);
    Data_storeRunMeasurement(&live.liveRun, &live.lastMeasurement);
}

void State_stopRun(void) {
    live.sessionState = APP_LIVESTATE_SESSION_STOPPED;
    live.speed        = 0;
    live.rpm          = 0;
    live.bpm          = 0;
    live.time         = "00:00:00";

    live.updateChart = 1;
    live.running     = 0;
}