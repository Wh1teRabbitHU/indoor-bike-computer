#include "data.h"

void Data_createRun(Data_Run* run) {}

void Data_createRunMeasurement(Data_Run* run, Data_RunMeasurement* measurement) {}

uint32_t Data_countRuns(void) { return 0; }

uint32_t Data_countRunMeasurements(uint32_t runIndex) { return 0; }

void Data_readRun(uint32_t runIndex, Data_Run* run) {}

void Data_readRunMeasurement(uint32_t runIndex, uint32_t measurementIndex, Data_RunMeasurement* measurement) {}

void Data_updateRun(Data_Run* run) {}

void Data_updateRunMeasurement(Data_Run* run, Data_RunMeasurement* measurement) {}

void Data_deleteRun(uint32_t runIndex) {}

void Data_deleteRunMeasurement(uint32_t runIndex, uint32_t measurementIndex) {}
