#include "data.h"

const char* attrSeparator = ";";
static Data_Statistics statistics = {0};

PRIVATE void Data_runPath(char* pathBuffer, const uint32_t runIndex) {
    sprintf(pathBuffer, "%s/%s%05lu/%s", DATA_RUNS_DIRECTORY_PATH, DATA_RUN_NAME_PREFIX, runIndex,
            DATA_RUN_SUMMARY_FILENAME);
}

PRIVATE void Data_measurementsPath(char* pathBuffer, const uint32_t runIndex) {
    sprintf(pathBuffer, "%s/%s%05lu/%s", DATA_RUNS_DIRECTORY_PATH, DATA_RUN_NAME_PREFIX, runIndex,
            DATA_RUN_MEASUREMENTS_FILENAME);
}

PRIVATE void Data_parseRun(char* data, Data_Run* run) {
    Data_RunAttr_t attrPointer = 0;
    char* attr = strtok(data, attrSeparator);
    char* endptr;

    while (attr != NULL) {
        switch (attrPointer) {
            case DATA_RUN_ATTR_NAME:
                strcpy(run->name, attr);
                break;
            case DATA_RUN_ATTR_CREATED:
                strcpy(run->created, attr);
                break;
            case DATA_RUN_ATTR_SESSION_LENGTH:
                run->sessionLength = strtol(attr, &endptr, 10);
                break;
            case DATA_RUN_ATTR_DISTANCE:
                run->distance = strtol(attr, &endptr, 10);
                break;
            case DATA_RUN_ATTR_AVG_DIFFICULTY:
                run->avgDifficulty = strtol(attr, &endptr, 10);
                break;
            case DATA_RUN_ATTR_AVG_SPEED:
                run->avgSpeed = strtol(attr, &endptr, 10);
                break;
            case DATA_RUN_ATTR_AVG_RPM:
                run->avgRpm = strtol(attr, &endptr, 10);
                break;
            case DATA_RUN_ATTR_AVG_BPM:
                run->avgBpm = strtol(attr, &endptr, 10);
                break;
            case DATA_RUN_ATTR_UNKNOWN:
                return;
        }

        attr = strtok(NULL, attrSeparator);
        attrPointer++;
    }
}

PRIVATE void Data_parseMeasurement(char* data, Data_RunMeasurement* measurement) {
    Data_MeasurementAttr_t attrPointer = 0;
    char* attr = strtok(data, attrSeparator);
    char* endptr;

    while (attr != NULL) {
        switch (attrPointer) {
            case DATA_MEASUREMENT_ATTR_TIMESTAMP:
                measurement->timestamp = strtol(attr, &endptr, 10);
                break;
            case DATA_MEASUREMENT_ATTR_DIFFICULTY:
                measurement->difficulty = strtol(attr, &endptr, 10);
                break;
            case DATA_MEASUREMENT_ATTR_SPEED:
                measurement->speed = strtol(attr, &endptr, 10);
                break;
            case DATA_MEASUREMENT_ATTR_RPM:
                measurement->rpm = strtol(attr, &endptr, 10);
                break;
            case DATA_MEASUREMENT_ATTR_BPM:
                measurement->bpm = strtol(attr, &endptr, 10);
                break;
            case DATA_MEASUREMENT_ATTR_UNKNOWN:
                return;
        }

        attr = strtok(NULL, attrSeparator);
        attrPointer++;
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
    SDCard_unmount("/");

    statistics.runs = stats.folders;

    return 1;
}

void Data_initRun(Data_Run* run) {
    char nameBuffer[DATA_RUN_NAME_MAX_LENGTH] = {0};

    statistics.runs++;

    sprintf(nameBuffer, "%s%05lu", DATA_RUN_NAME_PREFIX, statistics.runs);

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
    char pathBuffer[SDCARD_MAX_FILE_NAME_SIZE] = {0};

    sprintf(pathBuffer, "%s/%s%05lu/%s", DATA_RUNS_DIRECTORY_PATH, DATA_RUN_NAME_PREFIX, runIndex,
            DATA_RUN_MEASUREMENTS_FILENAME);

    result = SDCard_mount("/");

    if (result != FR_OK || !SDCard_pathExists(pathBuffer)) {
        return 0;
    }

    SDCard_FileStatistics statistics = {0};

    SDCard_fileStatistics(pathBuffer, &statistics);
    SDCard_unmount("/");

    return statistics.lines;
}

uint8_t Data_readRun(uint32_t runIndex, Data_Run* run) {
    FRESULT result;
    char pathBuffer[SDCARD_MAX_FILE_NAME_SIZE] = {0};
    char data[SDCARD_MAX_LINE_SIZE] = {0};

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
    char pathBuffer[SDCARD_MAX_FILE_NAME_SIZE] = {0};
    char line[SDCARD_MAX_LINE_SIZE] = {0};

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
    char pathBuffer[SDCARD_MAX_FILE_NAME_SIZE] = {0};

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
    SDCard_unmount("/");

    if (result != FR_OK) {
        return 0;
    }

    page->endOfRun = linePage.endOfFile;
    page->resultSize = linePage.resultSize;

    for (uint8_t i = 0; i < linePage.resultSize; i++) {
        char* line = linePage.lines[i];
        Data_RunMeasurement measurement = page->measurements[i];

        Data_parseMeasurement(line, &measurement);
    }

    return 1;
}

uint8_t Data_storeRun(Data_Run* run) {
    FRESULT result;
    char pathBuffer[SDCARD_MAX_FILE_NAME_SIZE] = {0};
    char dataBuffer[SDCARD_MAX_LINE_SIZE] = {0};

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

    sprintf(pathBuffer, "%s/%s/%s", DATA_RUNS_DIRECTORY_PATH, run->name, DATA_RUN_SUMMARY_FILENAME);
    sprintf(dataBuffer, "%s;%s;%lu;%lu;%d;%lu;%lu;%lu", run->name, run->created, run->sessionLength, run->distance,
            run->avgDifficulty, run->avgSpeed, run->avgRpm, run->avgBpm);

    result = SDCard_writeFile(pathBuffer, dataBuffer);
    SDCard_unmount("/");

    return result == FR_OK ? 1 : 0;
}

uint8_t Data_storeRunMeasurement(Data_Run* run, Data_RunMeasurement* measurement) {
    FRESULT result;
    char pathBuffer[SDCARD_MAX_FILE_NAME_SIZE] = {0};
    char dataBuffer[SDCARD_MAX_LINE_SIZE] = {0};

    result = SDCard_mount("/");

    if (result != FR_OK) {
        return 0;
    }

    sprintf(pathBuffer, "%s/%s/%s", DATA_RUNS_DIRECTORY_PATH, run->name, DATA_RUN_MEASUREMENTS_FILENAME);
    sprintf(dataBuffer, "%lu;%d;%lu;%lu;%lu\n", measurement->timestamp, measurement->difficulty, measurement->speed,
            measurement->rpm, measurement->bpm);

    result = SDCard_appendFile(pathBuffer, dataBuffer);
    SDCard_unmount("/");

    return result == FR_OK ? 1 : 0;
}

uint8_t Data_deleteRun(uint32_t runIndex) { return 1; }
