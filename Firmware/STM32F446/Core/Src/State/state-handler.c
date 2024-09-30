#include "state-handler.h"

static State_Global global = {.infoMessage = NULL, .errorMessage = NULL, .updateLevel = 0};
static State_Live live = {.difficulty = 0,
                          .speed = 0,
                          .rpm = 0,
                          .bpm = 0,
                          .updateChart = 0,
                          .sessionState = APP_LIVESTATE_SESSION_STOPPED,
                          .running = 0};

State_Global* State_Global_get(void) { return &global; }

State_Live* State_Live_get(void) { return &live; }

void State_Live_start() {
    if (!live.running) {
        Data_Run run = {0};
        Data_RunMeasurement measurement = {0};

        Data_initRun(&run);

        live.running = 1;
        live.liveRun = run;
        live.lastMeasurement = measurement;
    }

    live.sessionState = APP_LIVESTATE_SESSION_RUNNING;
}

void State_Live_pause() { State_Live_get()->sessionState = APP_LIVESTATE_SESSION_PAUSED; }

void State_Live_update(char* timestamp) {
    live.time = timestamp;
    live.updateChart = 1;

    live.lastMeasurement.timestamp += 1;  // Add one second
    live.lastMeasurement.bpm = live.bpm;
    live.lastMeasurement.difficulty = live.difficulty;
    live.lastMeasurement.rpm = live.rpm;
    live.lastMeasurement.speed = live.speed;

    live.liveRun.sessionLength += 1;  // Add one second
    live.liveRun.distance += live.rpm / 60 * BIKE_WHEEL_CIRCUMFERENCE;

    if (live.liveRun.sessionLength == 1) {
        live.liveRun.avgBpm = live.bpm;
        live.liveRun.avgSpeed = live.speed;
        live.liveRun.avgRpm = live.rpm;
        live.liveRun.avgDifficulty = live.difficulty;
    } else {
        uint32_t avgCount = live.liveRun.sessionLength - 1;

        live.liveRun.avgBpm = (live.bpm + (live.liveRun.avgBpm * avgCount)) / (avgCount + 1);
        live.liveRun.avgSpeed = (live.speed + (live.liveRun.avgSpeed * avgCount)) / (avgCount + 1);
        live.liveRun.avgRpm = (live.rpm + (live.liveRun.avgRpm * avgCount)) / (avgCount + 1);
        live.liveRun.avgDifficulty = (live.difficulty + (live.liveRun.avgDifficulty * avgCount)) / (avgCount + 1);
    }

    Data_storeRun(&live.liveRun);
    Data_storeRunMeasurement(&live.liveRun, &live.lastMeasurement);
}

void State_Live_stop(void) {
    live.sessionState = APP_LIVESTATE_SESSION_STOPPED;
    live.speed = 0;
    live.rpm = 0;
    live.bpm = 0;
    live.time = "00:00:00";

    live.updateChart = 1;
    live.running = 0;
}