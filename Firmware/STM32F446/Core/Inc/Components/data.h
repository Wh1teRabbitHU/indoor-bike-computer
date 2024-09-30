#ifndef INC_DATA_H_
#define INC_DATA_H_

#include "macros.h"
#include "sd_card.h"

#define DATA_RUNS_DIRECTORY_PATH "/indoor-bike/runs"
#define DATA_RUN_SUMMARY_FILENAME "summary.txt"
#define DATA_RUN_MEASUREMENTS_FILENAME "measurements.txt"
#define DATA_RUN_NAME_PREFIX "run_"
#define DATA_RUN_NAME_MAX_LENGTH 10
#define DATA_RUN_TIMESTAMP_LENGTH 19
#define DATA_MEASUREMENTS_PAGE_SIZE SDCARD_CONTENT_PAGE_SIZE

typedef enum Data_RunAttr_t {
    DATA_RUN_ATTR_NAME = 0,
    DATA_RUN_ATTR_CREATED = 1,
    DATA_RUN_ATTR_SESSION_LENGTH = 2,
    DATA_RUN_ATTR_DISTANCE = 3,
    DATA_RUN_ATTR_AVG_DIFFICULTY = 4,
    DATA_RUN_ATTR_AVG_SPEED = 5,
    DATA_RUN_ATTR_AVG_RPM = 6,
    DATA_RUN_ATTR_AVG_BPM = 7,
    DATA_RUN_ATTR_UNKNOWN = 8
} Data_RunAttr_t;

typedef enum Data_MeasurementAttr_t {
    DATA_MEASUREMENT_ATTR_TIMESTAMP = 0,
    DATA_MEASUREMENT_ATTR_DIFFICULTY = 1,
    DATA_MEASUREMENT_ATTR_SPEED = 2,
    DATA_MEASUREMENT_ATTR_RPM = 3,
    DATA_MEASUREMENT_ATTR_BPM = 4,
    DATA_MEASUREMENT_ATTR_UNKNOWN = 5
} Data_MeasurementAttr_t;

typedef struct Data_Statistics {
    uint32_t runs;            // Run count
    uint32_t sessionsLength;  // In seconds
    uint32_t distanceSum;     // In meters
} Data_Statistics;

// Max data length: 53
typedef struct Data_Run {
    char name[DATA_RUN_NAME_MAX_LENGTH];      // Maximum 10 char
    char created[DATA_RUN_TIMESTAMP_LENGTH];  // Timestamp: 2024-01-01 00:00:00, 19 char
    uint32_t sessionLength;                   // In seconds, max 5 char long 99999
    uint32_t distance;                        // In centimeters, max 8 char long: 99999999
    uint8_t avgDifficulty;                    // Percentage value, 3 char
    uint32_t avgSpeed;                        // Km/h / 100, example: 12.34km/h -> 1234, 4 char
    uint32_t avgRpm;                          // Bike wheel rotation per minute, 3 char
    uint32_t avgBpm;                          // Heartbeat per minute, 3 char
} Data_Run;

typedef struct Data_RunMeasurement {
    uint32_t timestamp;  // In seconds
    uint8_t difficulty;  // Percentage value
    uint32_t speed;      // Km/h / 100, example: 12.34km/h -> 1234
    uint32_t rpm;        // Bike wheel rotation per minute
    uint32_t bpm;        // Heartbeat per minute
} Data_RunMeasurement;

typedef struct Data_RunMeasurementPage {
    Data_RunMeasurement measurements[DATA_MEASUREMENTS_PAGE_SIZE];
    uint32_t startIndex;
    uint8_t resultSize;
    uint8_t endOfRun;
} Data_RunMeasurementPage;

/** Create folder structure on the SD card. It returns the state of the initialization. */
uint8_t Data_initStorage(void);

void Data_initRun(Data_Run* run);

/** Counts the available runs on the SD card.
 * This relies on unmodified folder structure inside the runs directory! */
uint32_t Data_countRuns(void);

/** Counts the run measurement entries of a given run. */
uint32_t Data_countRunMeasurements(uint32_t runIndex);

/**
 * Reads out the run on the given index.
 * Index is dependent on the order of the files, so if the naming is different from the creation order, it won't take in
 * a chronological order! */
uint8_t Data_readRun(uint32_t runIndex, Data_Run* run);

/**
 * Loads a measurement value from a run on the given index using the measurement index.
 * Measurements are stored in one file and the order of the measurement defines the indexed position! */
uint8_t Data_readRunMeasurement(uint32_t runIndex, uint32_t measurementIndex, Data_RunMeasurement* measurement);
uint8_t Data_readRunMeasurements(uint32_t runIndex, Data_RunMeasurementPage* page);
uint8_t Data_storeRun(Data_Run* run);
uint8_t Data_storeRunMeasurement(Data_Run* run, Data_RunMeasurement* measurement);
uint8_t Data_deleteRun(uint32_t runIndex);

#endif