#ifndef INC_CONFIG_H_
#define INC_CONFIG_H_

#include "macros.h"
#include "sd_card.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"

#define CONFIG_GLOBAL_PATH               "/indoor-bike/configuration.txt"

#define CONFIG_WIFI_SSID_LENGTH          32
#define CONFIG_WIFI_PASSWORD_LENGTH      32
#define CONFIG_DIFICULTY_STEPS_COUNT     11

#define CONFIG_WIFI_ENABLED_KEY          "wifi_enabled"
#define CONFIG_WIFI_SSID_KEY             "wifi_ssid"
#define CONFIG_WIFI_PASSWORD_KEY         "wifi_password"
#define CONFIG_DIFICULTY_INCREMENTAL_KEY "difficulty_incremental"
#define CONFIG_DIFICULTY_STEPS_KEY       "difficulty_steps"
#define CONFIG_BIKE_RPM_SPEED_RATIO_KEY  "bike_rpm_speed_ratio"

typedef struct Config_Wifi {
    uint8_t enabled;
    char ssid[CONFIG_WIFI_SSID_LENGTH];
    char password[CONFIG_WIFI_PASSWORD_LENGTH];
} Config_Wifi;

typedef struct Config_Difficulty {
    uint8_t incremental;                          // Defines the direction of the difficulty change of the raw measurment value.
    uint16_t steps[CONFIG_DIFICULTY_STEPS_COUNT]; // Each step is a raw mV value of the measured difficulty, every step is 10%, from 0% to 100%
} Config_Difficulty;

typedef struct Config_Bike {
    Config_Difficulty difficulty;
    uint32_t rpmSpeedRatio; // This defines the RPM-to-speed ratio. 80 rpm with 25 km/h has a 31.25 ratio. This value is stored as ratio * 100 = 3125
} Config_Bike;

typedef struct Config_Global {
    Config_Wifi wifi;
    Config_Bike bike;
} Config_Global;

void Config_load(void);
void Config_save(void);
Config_Global * Config_get(void);

#endif
