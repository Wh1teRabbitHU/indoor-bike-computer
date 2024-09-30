#ifndef __BIKE_H
#define __BIKE_H

#include "gui.h"
#include "mcp3421.h"
#include "state-handler.h"
#include "stdint.h"
#include "stdio.h"

#define BIKE_WHEEL_CIRCUMFERENCE 80
#define BIKE_WHEEL_SPEED_RATIO 25

void Bike_setInfo(char* info);
void Bike_setError(char* error);
void Bike_clearInfo(void);
void Bike_clearError(void);

void Bike_updateDifficulty(void);
void Bike_updateRevolution(void);

#endif