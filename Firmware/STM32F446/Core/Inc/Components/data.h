#ifndef INC_DATA_H_
#define INC_DATA_H_

#include "macros.h"
#include "sd_card.h"

#define DATA_RUNS_DIRECTORY_PATH       "/indoor-bike/runs"
#define DATA_RUNS_STATISTICS_FILENAME  "statistics.txt"
#define DATA_RUN_SUMMARY_FILENAME      "summary.txt"
#define DATA_RUN_MEASUREMENTS_FILENAME "measurements.txt"
#define DATA_RUN_NAME_PREFIX           "run_"
#define DATA_RUN_NAME_MAX_LENGTH       10
#define DATA_RUN_TIMESTAMP_LENGTH      19
#define DATA_RUNS_PAGE_SIZE            SDCARD_DIR_PAGE_SIZE
#define DATA_MEASUREMENTS_PAGE_SIZE    SDCARD_CONTENT_PAGE_SIZE

typedef enum Data_StatisticsAttr_t {
    DATA_STATISTICS_ATTR_RUNS           = 0,
    DATA_STATISTICS_ATTR_SESSION_LENGTH = 1,
    DATA_STATISTICS_ATTR_DISTANCE_SUM   = 2,
    DATA_STATISTICS_ATTR_UNKNOWN        = 3,
} Data_StatisticsAttr_t;

typedef enum Data_RunAttr_t {
    DATA_RUN_ATTR_NAME           = 0,
    DATA_RUN_ATTR_CREATED        = 1,
    DATA_RUN_ATTR_SESSION_LENGTH = 2,
    DATA_RUN_ATTR_DISTANCE       = 3,
    DATA_RUN_ATTR_AVG_DIFFICULTY = 4,
    DATA_RUN_ATTR_AVG_SPEED      = 5,
    DATA_RUN_ATTR_AVG_RPM        = 6,
    DATA_RUN_ATTR_AVG_BPM        = 7,
    DATA_RUN_ATTR_UNKNOWN        = 8
} Data_RunAttr_t;

typedef enum Data_MeasurementAttr_t {
    DATA_MEASUREMENT_ATTR_TIMESTAMP  = 0,
    DATA_MEASUREMENT_ATTR_DIFFICULTY = 1,
    DATA_MEASUREMENT_ATTR_SPEED      = 2,
    DATA_MEASUREMENT_ATTR_RPM        = 3,
    DATA_MEASUREMENT_ATTR_BPM        = 4,
    DATA_MEASUREMENT_ATTR_UNKNOWN    = 5
} Data_MeasurementAttr_t;

typedef struct Data_Statistics {
    uint32_t runs;           // Run count, maximum 10 digits (4 294 967 295 runs)
    uint32_t sessionsLength; // In seconds, maximum 10 digits (4 294 967 295 seconds, 71 582 788 min, 1 193 046 hours,
                             // 49 710 days, 136 years)
    uint32_t distanceSum;    // In meters, maximum 10 digits (4 294 967 295 m, 4 294 967 km)
} Data_Statistics;

// Max data length: 53
typedef struct Data_Run {
    char name[DATA_RUN_NAME_MAX_LENGTH];     // Maximum 10 char
    char created[DATA_RUN_TIMESTAMP_LENGTH]; // Timestamp: 2024-01-01 00:00:00, 19 char
    uint32_t sessionLength;                  // In seconds, max 5 char long 99999
    uint32_t distance;                       // In centimeters, max 8 char long: 99999999
    uint8_t avgDifficulty;                   // Percentage value, 3 char
    uint32_t avgSpeed;                       // Km/h * 100, example: 1234 -> 12.34km/h, 4 char
    uint32_t avgRpm;                         // Bike wheel rotation per minute, 3 char
    uint32_t avgBpm;                         // Heartbeat per minute, 3 char
} Data_Run;

typedef struct Data_RunPage {
    char runs[DATA_RUNS_PAGE_SIZE][DATA_RUN_NAME_MAX_LENGTH];
    uint32_t startIndex;
    uint8_t resultSize;
    uint8_t endOfList;
} Data_RunPage;

typedef struct Data_RunMeasurement {
    uint32_t timestamp; // In seconds
    uint8_t difficulty; // Percentage value
    uint32_t speed;     // Km/h * 100, example: 1234 -> 12.34km/h
    uint32_t rpm;       // Bike wheel rotation per minute
    uint32_t bpm;       // Heartbeat per minute
} Data_RunMeasurement;

typedef struct Data_RunMeasurementPage {
    Data_RunMeasurement measurements[DATA_MEASUREMENTS_PAGE_SIZE];
    uint32_t startIndex;
    uint8_t resultSize;
    uint8_t endOfRun;
} Data_RunMeasurementPage;

/** Create folder structure on the SD card. It returns the state of the initialization. */
uint8_t Data_initStorage(void);

void Data_initRun(Data_Run * run);

/** Counts the available runs on the SD card.
 * This relies on unmodified folder structure inside the runs directory! */
uint32_t Data_countRuns(void);

/**
 * @brief Counts the run measurement entries of a given run.
 *
 * @param runName Name of the run you want to read from the SD card
 * @return uint32_t The available measurements for the given run
 */
uint32_t Data_countRunMeasurements(char * runName);

/**
 * @brief This method is reading the stored statistics of all time runs, including roun count, distance and length. The
 * result is stored internally in the module and can be accessed with the `Data_getStatistics` method after
 * initialization.
 *
 * @return uint8_t `1` if the data load was successful
 */
uint8_t Data_loadStatistics();

uint8_t Data_saveStatistics();

/**
 * @brief Reads out the run with the given name. If the run doesn't exist, it returns `0`.
 *
 * @param runName Name of the run you want to read from the SD card
 * @param run The object where the result is loaded into
 * @return `1` if the run exists and the read was successful, `0` if something went wrong
 */
uint8_t Data_readRun(char * runName, Data_Run * run);

/**
 * @brief Reads the available runs using a page object. Before you call the method, set the `startIndex`. If you want to
 * go through all runs, call this method recursively and increment the `startIndex` every time with the page size until
 * the `endOfList` variable becomes `1`. Rely on the `resultSize` variable whenever you read out the result!
 *
 * @param page
 * @return uint8_t `1` if the read was successful, `0` if something went wrong
 */
uint8_t Data_readRuns(Data_RunPage * page);

/**
 * @brief Loads a measurement value from a run with the given name using the measurement index. Measurements are stored
 * in one file and the order of the measurement defines the indexed position!
 *
 * @param runName Name of the run you want to read from the SD card
 * @param measurementIndex Index of the measurement, depends on the order in the file
 * @param measurement The object where the function will load the result into, if the read suceeded
 * @return uint8_t `1` if the read was successful, `0` if something went wrong
 */
uint8_t Data_readRunMeasurement(char * runName, uint32_t measurementIndex, Data_RunMeasurement * measurement);
uint8_t Data_readRunMeasurements(char * runName, Data_RunMeasurementPage * page);
uint8_t Data_storeRun(Data_Run * run);
uint8_t Data_storeRunMeasurement(Data_Run * run, Data_RunMeasurement * measurement);
uint8_t Data_deleteRun(Data_Run * run);
uint8_t Data_addRunToStatistics(Data_Run * run);
uint8_t Data_removeRunFromStatistics(Data_Run * run);
Data_Statistics * Data_getStatistics();

#endif