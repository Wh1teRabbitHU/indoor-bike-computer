#include "data.h"

const char* attrSeparator = ";";
static Data_Statistics statistics = {0};

PRIVATE void Data_runPath(char* pathBuffer, const uint32_t runIndex) {
    sprintf(pathBuffer, "%s/%s%05lu/%s", DATA_RUNS_DIRECTORY_PATH, DATA_RUNS_NAME_PREFIX, runIndex,
            DATA_RUNS_SUMMARY_FILENAME);
}
PRIVATE void Data_measurementsPath(char* pathBuffer, const uint32_t runIndex) {
    sprintf(pathBuffer, "%s/%s%05lu/%s", DATA_RUNS_DIRECTORY_PATH, DATA_RUNS_NAME_PREFIX, runIndex,
            DATA_RUNS_MEASUREMENTS_FILENAME);
}

PRIVATE void Data_parseRun(char* data, Data_Run* run) {
    uint8_t attrCount = 0;
    char* attr = strtok(data, attrSeparator);
    char* endptr;

    while (attr != NULL) {
        switch (attrCount) {
            case 0:  // name
                strcpy(run->name, attr);
                break;
            case 1:  // created
                strcpy(run->created, attr);
                break;
            case 2:  // sessionLength
                run->sessionLength = strtol(attr, &endptr, 10);
                break;
            case 3:  // distance
                run->distance = strtol(attr, &endptr, 10);
                break;
            case 4:  // avgDifficulty
                run->avgDifficulty = strtol(attr, &endptr, 10);
                break;
            case 5:  // avgSpeed
                run->avgSpeed = strtol(attr, &endptr, 10);
                break;
            case 6:  // avgRpm
                run->avgRpm = strtol(attr, &endptr, 10);
                break;
            case 7:  // avgBpm
                run->avgBpm = strtol(attr, &endptr, 10);
                break;
        }

        attr = strtok(NULL, attrSeparator);
        attrCount++;
    }
}

PRIVATE void Data_parseMeasurement(char* data, Data_RunMeasurement* measurement) {
    uint8_t attrCount = 0;
    char* attr = strtok(data, attrSeparator);
    char* endptr;

    while (attr != NULL) {
        switch (attrCount) {
            case 0:  // timestamp
                measurement->timestamp = strtol(attr, &endptr, 10);
                break;
            case 1:  // difficulty
                measurement->difficulty = strtol(attr, &endptr, 10);
                break;
            case 2:  // speed
                measurement->speed = strtol(attr, &endptr, 10);
                break;
            case 3:  // rpm
                measurement->rpm = strtol(attr, &endptr, 10);
                break;
            case 4:  // bpm
                measurement->bpm = strtol(attr, &endptr, 10);
                break;
        }

        attr = strtok(NULL, attrSeparator);
        attrCount++;
    }
}

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

    SDCard_DirectoryStatistics stats = {0};

    SDCard_directoryStatistics(DATA_RUNS_DIRECTORY_PATH, &stats);

    statistics.runs = stats.folders;

    SDCard_unmount("/");

    return 1;
}

void Data_initRun(Data_Run* run) {
    char nameBuffer[DATA_RUN_NAME_MAX_LENGTH] = {0};

    statistics.runs++;

    sprintf(nameBuffer, "%s%05lu", DATA_RUNS_NAME_PREFIX, statistics.runs);

    strcpy(run->name, nameBuffer);
    strcpy(run->created, "2024-01-01 10:10:10");

    run->sessionLength = 0;
    run->distance = 0;
    run->avgDifficulty = 0;
    run->avgSpeed = 0;
    run->avgRpm = 0;
    run->avgBpm = 0;
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

uint32_t Data_countRunMeasurements(uint32_t runIndex) {
    FRESULT result;
    char pathBuffer[128] = {0};

    sprintf(pathBuffer, "%s/%s%05lu/%s", DATA_RUNS_DIRECTORY_PATH, DATA_RUNS_NAME_PREFIX, runIndex,
            DATA_RUNS_MEASUREMENTS_FILENAME);

    result = SDCard_mount("/");

    if (result != FR_OK) {
        return 0;
    } else if (!SDCard_pathExists(pathBuffer)) {
        return 0;
    }

    SDCard_FileStatistics statistics = {0};

    SDCard_fileStatistics(pathBuffer, &statistics);

    SDCard_unmount("/");

    return statistics.lines;
}

uint8_t Data_readRun(uint32_t runIndex, Data_Run* run) {
    FRESULT result;
    char pathBuffer[128] = {0};
    char data[128] = {0};

    result = SDCard_mount("/");

    if (result != FR_OK) {
        return 0;
    }

    Data_runPath(pathBuffer, runIndex);

    if (!SDCard_pathExists(pathBuffer)) {
        return 0;
    }

    result = SDCard_readFile(pathBuffer, data, 64);

    SDCard_unmount("/");

    if (result != FR_OK) {
        return 0;
    }

    Data_parseRun(data, run);

    return 1;
}

uint8_t Data_readRunMeasurement(uint32_t runIndex, uint32_t measurementIndex, Data_RunMeasurement* measurement) {
    FRESULT result;
    char pathBuffer[128] = {0};
    char line[128] = {0};

    result = SDCard_mount("/");

    if (result != FR_OK) {
        return 0;
    }

    Data_measurementsPath(pathBuffer, runIndex);

    if (!SDCard_pathExists(pathBuffer)) {
        SDCard_unmount("/");
        return 0;
    }

    result = SDCard_readLine(pathBuffer, line, measurementIndex);

    SDCard_unmount("/");

    if (result != FR_OK) {
        return 0;
    }

    Data_parseMeasurement(line, measurement);

    return 1;
}

uint8_t Data_readRunMeasurements(uint32_t runIndex, Data_RunMeasurementPage* page) {
    FRESULT result;
    char pathBuffer[128] = {0};

    result = SDCard_mount("/");

    if (result != FR_OK) {
        return 0;
    }

    Data_measurementsPath(pathBuffer, runIndex);

    if (!SDCard_pathExists(pathBuffer)) {
        SDCard_unmount("/");
        return 0;
    }

    SDCard_LinesPage linePage = {.startIndex = page->startIndex, 0};

    result = SDCard_readLines(pathBuffer, &linePage);

    if (result != FR_OK) {
        SDCard_unmount("/");
        return 0;
    }

    page->endOfRun = linePage.endOfFile;
    page->resultSize = linePage.resultSize;

    for (uint8_t i = 0; i < linePage.resultSize; i++) {
        char* line = linePage.lines[i];
        Data_RunMeasurement measurement = page->measurements[i];

        Data_parseMeasurement(line, &measurement);
    }

    SDCard_unmount("/");

    return 1;
}

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
    sprintf(dataBuffer, "%s;%s;%lu;%lu;%d;%lu;%lu;%lu", run->name, run->created, run->sessionLength, run->distance,
            run->avgDifficulty, run->avgSpeed, run->avgRpm, run->avgBpm);

    result = SDCard_writeFile(pathBuffer, dataBuffer);

    if (result != FR_OK) {
        return 0;
    }

    SDCard_unmount("/");

    return 1;
}

uint8_t Data_storeRunMeasurement(Data_Run* run, Data_RunMeasurement* measurement) {
    volatile FRESULT result;

    char pathBuffer[128] = {0};
    char dataBuffer[128] = {0};

    result = SDCard_mount("/");

    if (result != FR_OK) {
        return 0;
    }

    sprintf(pathBuffer, "%s/%s/%s", DATA_RUNS_DIRECTORY_PATH, run->name, DATA_RUNS_MEASUREMENTS_FILENAME);
    sprintf(dataBuffer, "%lu;%d;%lu;%lu;%lu\n", measurement->timestamp, measurement->difficulty, measurement->speed,
            measurement->rpm, measurement->bpm);

    result = SDCard_appendFile(pathBuffer, dataBuffer);

    SDCard_unmount("/");

    return result == FR_OK ? 1 : 0;
}

uint8_t Data_deleteRun(uint32_t runIndex) { return 1; }
