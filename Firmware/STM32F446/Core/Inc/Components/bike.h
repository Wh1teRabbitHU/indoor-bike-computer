#ifndef __BIKE_H
#define __BIKE_H

#include "gui.h"
#include "mcp3421.h"
#include "state.h"
#include "stdint.h"
#include "stdio.h"

#define BIKE_WHEEL_SPEED_RATIO         31.25                          // 80 RPM = 25 km/h = 2500 speed unit ; speed unit = X km/h * 100

#define BIKE_CALCULATE_RPM(msElapsed)  (60 / ((msElapsed) / 1000.0))
#define BIKE_CALCULATE_SPEED(rpm)      (rpm * BIKE_WHEEL_SPEED_RATIO) // speed unit = km/h * 100
#define BIKE_CALCULATE_DISTANCE(speed) ((speed * 1000) / 60 / 60)     // speed unit -> cm/h -> cm/min -> cm/s

void Bike_init(TIM_HandleTypeDef * revolutionTimer);
void Bike_setInfo(char * info);
void Bike_setError(char * error);
void Bike_clearInfo(void);
void Bike_clearError(void);

void Bike_updateDifficulty(void);
void Bike_updateRevolution(void);

#endif