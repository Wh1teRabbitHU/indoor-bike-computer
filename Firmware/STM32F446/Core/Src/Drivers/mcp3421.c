#include "mcp3421.h"

static I2C_HandleTypeDef * i2c = NULL;
static MCP3421_config currentConfig =
    {ready : 0, mode : MCP3421_MODE_CONTINUOUS, sampleRate : MCP3421_RATE_240_00, gain : MCP3421_GAIN_1X};

PRIVATE HAL_StatusTypeDef MCP3421_writeI2C(uint8_t data) {
    uint8_t buffer[1];

    buffer[0] = data;

    HAL_StatusTypeDef result = HAL_I2C_Master_Transmit(i2c, MCP3421_I2C_ADDR, buffer, 1, 100);

    if (result != HAL_OK) {
        Bike_setError("Error: Couldn't write to the ADC register");
    }

    return result;
}

PRIVATE HAL_StatusTypeDef MCP3421_readI2C(uint8_t * buffer) {
    uint8_t dataLength       = currentConfig.sampleRate == MCP3421_RATE_003_75 ? 4 : 3;
    HAL_StatusTypeDef result = HAL_I2C_Master_Receive(i2c, MCP3421_I2C_ADDR, buffer, dataLength, 100);

    if (result != HAL_OK) {
        Bike_setError("Error: Couldn't read from the ADC register");
    }

    return result;
}

PRIVATE void MCP3421_setConfig(uint8_t configBin, MCP3421_config * config) {
    config->ready      = binary_getBit8(configBin, 7);
    config->mode       = binary_getBit8(configBin, 4);
    config->sampleRate = (binary_getBit8(configBin, 3) << 1) | binary_getBit8(configBin, 2);
    config->gain       = (binary_getBit8(configBin, 1) << 1) | binary_getBit8(configBin, 0);
}

HAL_StatusTypeDef MCP3421_init(I2C_HandleTypeDef * _i2c) {
    i2c = _i2c;

    MCP3421_config config = {0};

    config.mode       = MCP3421_MODE_CONTINUOUS;
    config.sampleRate = MCP3421_RATE_003_75;
    config.gain       = MCP3421_GAIN_1X;

    return MCP3421_writeConfig(&config);
}

HAL_StatusTypeDef MCP3421_readConfig(MCP3421_config * config) {
    uint8_t buffer[4] = {0};

    HAL_StatusTypeDef result = MCP3421_readI2C(buffer);

    uint8_t configByte = currentConfig.sampleRate == MCP3421_RATE_003_75 ? 3 : 2;
    uint8_t configBin  = buffer[configByte];

    MCP3421_setConfig(configBin, config);
    MCP3421_setConfig(configBin, &currentConfig);

    return result;
}

HAL_StatusTypeDef MCP3421_writeConfig(MCP3421_config * config) {
    uint8_t configBin = 0;

    configBin = configBin | config->ready << 7;
    configBin = configBin | config->mode << 4;
    configBin = configBin | binary_getBit8(config->sampleRate, 1) << 3;
    configBin = configBin | binary_getBit8(config->sampleRate, 0) << 2;
    configBin = configBin | binary_getBit8(config->gain, 1) << 1;
    configBin = configBin | binary_getBit8(config->gain, 0);

    HAL_StatusTypeDef result = MCP3421_writeI2C(configBin);

    if (result == HAL_OK) {
        MCP3421_setConfig(configBin, &currentConfig);
    }

    return result;
}

uint32_t MCP3421_readMeasurement() {
    uint8_t buffer[4]        = {0};
    HAL_StatusTypeDef result = MCP3421_readI2C(buffer);

    if (result != HAL_OK) {
        return 0;
    }

    uint32_t measurement = 0;

    measurement = measurement | buffer[2];
    measurement = measurement | buffer[1] << 8;
    measurement = measurement | ((buffer[0] & 0b11) << 16);

    switch (currentConfig.sampleRate) {
    case MCP3421_RATE_240_00:
        measurement *= MCP3421_UNIT_240_00;
        break;
    case MCP3421_RATE_060_00:
        measurement *= MCP3421_UNIT_060_00;
        break;
    case MCP3421_RATE_015_00:
        measurement *= MCP3421_UNIT_015_00;
        break;
    case MCP3421_RATE_003_75:
        measurement *= MCP3421_UNIT_003_75;
        break;
    }

    switch (currentConfig.gain) {
    case MCP3421_GAIN_1X:
        break;
    case MCP3421_GAIN_2X:
        measurement *= 2;
        break;
    case MCP3421_GAIN_4X:
        measurement *= 4;
        break;
    case MCP3421_GAIN_8X:
        measurement *= 8;
        break;
    }

    measurement = MCP3421_CALCULATE_MEASUREMENT(measurement);

    return measurement;
}