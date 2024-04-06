#ifndef __BIKE_H
#define __BIKE_H

#include "app-state.h"
#include "gui.h"
#include "mcp3421.h"
#include "stdint.h"
#include "stdio.h"

void Bike_setInfo(char* info);
void Bike_setError(char* error);
void Bike_clearInfo(void);
void Bike_clearError(void);
void Bike_setTime(RTC_TimeTypeDef* rtcTime);

void Bike_updateDifficulty(void);
void Bike_updateRevolution(void);

#endif