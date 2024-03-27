#ifndef __MCP3421_H
#define __MCP3421_H

#include "bike.h"
#include "binary.h"
#include "main.h"

#define MCP3421_I2C_ADDR 0b1101000 << 1

#define MCP3421_MODE_SINGLE 0b00
#define MCP3421_MODE_CONTINUOUS 0b01
#define MCP3421_RATE_240_00 0b00
#define MCP3421_RATE_060_00 0b01
#define MCP3421_RATE_015_00 0b10
#define MCP3421_RATE_003_75 0b11
#define MCP3421_UNIT_240_00 1
#define MCP3421_UNIT_060_00 0.25
#define MCP3421_UNIT_015_00 0.0625
#define MCP3421_UNIT_003_75 0.015625
#define MCP3421_GAIN_1X 0b00
#define MCP3421_GAIN_2X 0b01
#define MCP3421_GAIN_4X 0b10
#define MCP3421_GAIN_8X 0b11

typedef struct MCP3421_config {
    uint8_t ready;
    uint8_t mode;
    uint8_t sampleRate;
    uint8_t gain;
} MCP3421_config;

void MCP3421_init(I2C_HandleTypeDef* i2c);

void MCP3421_readConfig(MCP3421_config* config);
void MCP3421_writeConfig(MCP3421_config* config);
uint32_t MCP3421_readMeasurement();

#endif