#ifndef INC_DATA_H_
#define INC_DATA_H_

#include "sd_card.h"

typedef struct Data_Run {
    uint32_t runIndex;
    char* name;
    char* created;
    char* finished;
} Data_Run;

typedef struct Data_RunMeasurement {
    uint32_t runIndex;
    uint32_t measurementIndex;

    char* timestamp;
    uint32_t difficulty;
    uint32_t speed;
    uint32_t rpm;
    uint32_t bpm;
} Data_RunMeasurement;

void Data_createRun(Data_Run* run);
void Data_createRunMeasurement(Data_Run* run, Data_RunMeasurement* measurement);
uint32_t Data_countRuns(void);
uint32_t Data_countRunMeasurements(uint32_t runIndex);
void Data_readRun(uint32_t runIndex, Data_Run* run);
void Data_readRunMeasurement(uint32_t runIndex, uint32_t measurementIndex, Data_RunMeasurement* measurement);
void Data_updateRun(Data_Run* run);
void Data_updateRunMeasurement(Data_Run* run, Data_RunMeasurement* measurement);
void Data_deleteRun(uint32_t runIndex);
void Data_deleteRunMeasurement(uint32_t runIndex, uint32_t measurementIndex);

#endif