#include "config.h"

const char * keyValueSeparator   = "=";
const char * arrayValueSeparator = ";";

static Config_Global globalConfig = {0};

PRIVATE void Config_setDefaultValues(void) {
    globalConfig.wifi.enabled = 0;
    strcpy(globalConfig.wifi.ssid, "[YOUR WIFIS SSID]");
    strcpy(globalConfig.wifi.password, "[YOUR WIFIS PASSWORD]");
    globalConfig.bike.difficulty.incremental = 0;

    for (uint8_t i = 0; i < CONFIG_DIFICULTY_STEPS_COUNT; i++) {
        globalConfig.bike.difficulty.steps[i] = 2300 - (i * 100);
    }
    globalConfig.bike.rpmSpeedRatio = 3125;
}

PRIVATE void Config_parseLine(char * line) {
    char * key   = strtok(line, keyValueSeparator);
    char * value = strtok(NULL, keyValueSeparator);
    char * endptr;

    if (key == NULL || value == NULL) {
        return;
    }

    if (strcmp(key, CONFIG_WIFI_ENABLED_KEY) == 0) {
        uint8_t enabled           = strtol(value, &endptr, 10);
        globalConfig.wifi.enabled = enabled;
    } else if (strcmp(key, CONFIG_WIFI_SSID_KEY) == 0) {
        strcpy(globalConfig.wifi.ssid, value);
    } else if (strcmp(key, CONFIG_WIFI_PASSWORD_KEY) == 0) {
        strcpy(globalConfig.wifi.password, value);
    } else if (strcmp(key, CONFIG_DIFICULTY_INCREMENTAL_KEY) == 0) {
        uint8_t incremental                      = strtol(value, &endptr, 10);
        globalConfig.bike.difficulty.incremental = incremental;
    } else if (strcmp(key, CONFIG_DIFICULTY_STEPS_KEY) == 0) {
        uint8_t i   = 0;
        char * attr = strtok(value, arrayValueSeparator);

        while (attr != NULL && i < CONFIG_DIFICULTY_STEPS_COUNT) {
            uint16_t step = strtol(attr, &endptr, 10);
            attr          = strtok(NULL, arrayValueSeparator);

            globalConfig.bike.difficulty.steps[i] = step;
            i++;
        }
    } else if (strcmp(key, CONFIG_BIKE_RPM_SPEED_RATIO_KEY) == 0) {
        uint32_t ratio                  = strtol(value, &endptr, 10);
        globalConfig.bike.rpmSpeedRatio = ratio;
    }
}

PRIVATE void Config_storeWifiEnabled() {
    char lineBuffer[SDCARD_MAX_LINE_SIZE] = {0};

    sprintf(lineBuffer, "%s=%u\n", CONFIG_WIFI_ENABLED_KEY, globalConfig.wifi.enabled);

    SDCard_writeFile(CONFIG_GLOBAL_PATH, lineBuffer, 1);
}

PRIVATE void Config_storeWifiSSID() {
    char lineBuffer[SDCARD_MAX_LINE_SIZE] = {0};

    sprintf(lineBuffer, "%s=%s\n", CONFIG_WIFI_SSID_KEY, globalConfig.wifi.ssid);

    SDCard_writeFile(CONFIG_GLOBAL_PATH, lineBuffer, 1);
}

PRIVATE void Config_storeWifiPassword() {
    char lineBuffer[SDCARD_MAX_LINE_SIZE] = {0};

    sprintf(lineBuffer, "%s=%s\n", CONFIG_WIFI_PASSWORD_KEY, globalConfig.wifi.password);

    SDCard_writeFile(CONFIG_GLOBAL_PATH, lineBuffer, 1);
}

PRIVATE void Config_storeDifficultyIncremental() {
    char lineBuffer[SDCARD_MAX_LINE_SIZE] = {0};

    sprintf(lineBuffer, "%s=%u\n", CONFIG_DIFICULTY_INCREMENTAL_KEY, globalConfig.bike.difficulty.incremental);

    SDCard_writeFile(CONFIG_GLOBAL_PATH, lineBuffer, 1);
}

PRIVATE void Config_storeDifficultySteps() {
    char lineBuffer[SDCARD_MAX_LINE_SIZE] = {0};
    uint16_t * steps                      = globalConfig.bike.difficulty.steps;

    sprintf(lineBuffer, "%s=%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u\n", CONFIG_DIFICULTY_STEPS_KEY, steps[0], steps[1], steps[2], steps[3], steps[4], steps[5], steps[6], steps[7], steps[8], steps[9], steps[10]);

    SDCard_writeFile(CONFIG_GLOBAL_PATH, lineBuffer, 1);
}

PRIVATE void Config_storeRpmSpeedRatio() {
    char lineBuffer[SDCARD_MAX_LINE_SIZE] = {0};

    sprintf(lineBuffer, "%s=%lu\n", CONFIG_BIKE_RPM_SPEED_RATIO_KEY, globalConfig.bike.rpmSpeedRatio);

    SDCard_writeFile(CONFIG_GLOBAL_PATH, lineBuffer, 1);
}

void Config_load(void) {
    FRESULT result = SDCard_mount("/");

    if (result != FR_OK) {
        return;
    }

    if (!SDCard_pathExists(CONFIG_GLOBAL_PATH)) {
        SDCard_unmount("/");

        Config_setDefaultValues();
        Config_save();

        return;
    }

    SDCard_LinesPage page = {0};

    while (!page.endOfFile) {
        page.startIndex += page.resultSize;

        FRESULT result = SDCard_readLines(CONFIG_GLOBAL_PATH, &page);

        if (result != FR_OK) {
            SDCard_unmount("/");
            return;
        }

        for (uint8_t i = 0; i < page.resultSize; i++) {
            Config_parseLine(page.lines[i]);
        }
    }

    SDCard_unmount("/");
}

void Config_save(void) {
    FRESULT result = SDCard_mount("/");

    if (result != FR_OK) {
        return;
    }

    if (SDCard_pathExists(CONFIG_GLOBAL_PATH)) {
        result = SDCard_removeItem(CONFIG_GLOBAL_PATH);

        if (result != FR_OK) {
            SDCard_unmount("/");
            return;
        }
    }

    result = SDCard_createFile(CONFIG_GLOBAL_PATH);

    if (result != FR_OK) {
        SDCard_unmount("/");
        return;
    }

    SDCard_writeFile(CONFIG_GLOBAL_PATH, "# Wifi\n", 1);
    Config_storeWifiEnabled();
    Config_storeWifiSSID();
    Config_storeWifiPassword();

    SDCard_writeFile(CONFIG_GLOBAL_PATH, "# Bike\n", 1);
    Config_storeDifficultyIncremental();
    Config_storeDifficultySteps();
    Config_storeRpmSpeedRatio();

    SDCard_unmount("/");
}

Config_Global * Config_get(void) {
    return &globalConfig;
}