#ifndef INC_DATA_H_
#define INC_DATA_H_

#include "sd_card.h"

#define DATA_RUNS_DIRECTORY_PATH "/indoor-bike/runs"
#define DATA_RUNS_SUMMARY_FILENAME "summary.txt"

typedef struct Data_Statistics {
    uint32_t runs;
    uint32_t sessionsLength;  // in seconds
    uint32_t distanceSum;
} Data_Statistics;

typedef struct Data_Run {
    uint32_t index;
    char name[10];           // Maximum 10 char
    char created[19];        // Timestamp: 2024-01-01 00:00:00
    uint32_t sessionLength;  // in seconds
    uint32_t distance;       // In meters
    uint32_t avgDifficulty;
    uint32_t avgSpeed;  // km/h / 100
    uint32_t avgRpm;
    uint32_t avgBpm;
} Data_Run;

typedef struct Data_RunMeasurement {
    uint32_t runIndex;
    uint32_t measurementIndex;

    uint32_t timestamp;  // in seconds
    uint32_t difficulty;
    uint32_t speed;  // km/h / 100
    uint32_t rpm;
    uint32_t bpm;
} Data_RunMeasurement;

uint8_t Data_initStorage();
uint32_t Data_countRuns(void);
uint32_t Data_countRunMeasurements(uint32_t runIndex);
void Data_readRun(uint32_t runIndex, Data_Run* run);
void Data_readRunMeasurement(uint32_t runIndex, uint32_t measurementIndex, Data_RunMeasurement* measurement);
uint8_t Data_storeRun(Data_Run* run);
void Data_storeRunMeasurement(Data_Run* run, Data_RunMeasurement* measurement);
void Data_deleteRun(uint32_t runIndex);
void Data_deleteRunMeasurement(uint32_t runIndex, uint32_t measurementIndex);

#endif