#include "data.h"

uint8_t Data_initStorage() {
    FRESULT result;

    result = SDCard_mount("/");

    if (result != FR_OK) {
        return 0;
    }

    uint8_t alreadyExists = SDCard_pathExists(DATA_RUNS_DIRECTORY_PATH);

    if (!alreadyExists) {
        result = SDCard_createDirectory(DATA_RUNS_DIRECTORY_PATH);

        if (result != FR_OK) {
            SDCard_unmount("/");
            return 0;
        }
    }

    SDCard_unmount("/");

    return 1;
}

uint32_t Data_countRuns(void) {
    FRESULT result;
    SDCard_DirectoryStatistics stats = {0};

    result = SDCard_mount("/");

    if (result != FR_OK) {
        return 0;
    }

    SDCard_directoryStatistics(DATA_RUNS_DIRECTORY_PATH, &stats);
    SDCard_unmount("/");

    return stats.folders;
}

uint32_t Data_countRunMeasurements(uint32_t runIndex) { return 0; }

void Data_readRun(uint32_t runIndex, Data_Run* run) {}

void Data_readRunMeasurement(uint32_t runIndex, uint32_t measurementIndex, Data_RunMeasurement* measurement) {}

uint8_t Data_storeRun(Data_Run* run) {
    volatile FRESULT result;

    char pathBuffer[128] = {0};
    char dataBuffer[128] = {0};

    sprintf(pathBuffer, "%s/%s", DATA_RUNS_DIRECTORY_PATH, run->name);

    result = SDCard_mount("/");

    if (result != FR_OK) {
        return 0;
    }

    uint8_t alreadyExists = SDCard_pathExists(pathBuffer);

    if (!alreadyExists) {
        result = SDCard_createDirectory(pathBuffer);

        if (result != FR_OK) {
            SDCard_unmount("/");
            return 0;
        }
    }

    sprintf(pathBuffer, "%s/%s/%s", DATA_RUNS_DIRECTORY_PATH, run->name, DATA_RUNS_SUMMARY_FILENAME);
    sprintf(dataBuffer, "%s;%s;%lu;%lu;%lu;%lu;%lu;%lu", run->name, run->created, run->sessionLength, run->distance,
            run->avgDifficulty, run->avgSpeed, run->avgRpm, run->avgBpm);

    result = SDCard_writeFile(pathBuffer, dataBuffer);

    if (result != FR_OK) {
        return 0;
    }

    SDCard_unmount("/");

    return 1;
}

void Data_storeRunMeasurement(Data_Run* run, Data_RunMeasurement* measurement) {}

void Data_deleteRun(uint32_t runIndex) {}

void Data_deleteRunMeasurement(uint32_t runIndex, uint32_t measurementIndex) {}
