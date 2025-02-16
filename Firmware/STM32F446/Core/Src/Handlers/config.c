#include "config.h"

const char * keyValueSeparator   = "=";
const char * arrayValueSeparator = ";";

static Config_Global globalConfig = {0};

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
        uint8_t incremental                 = strtol(value, &endptr, 10);
        globalConfig.difficulty.incremental = incremental;
    } else if (strcmp(key, CONFIG_DIFICULTY_STEPS_KEY) == 0) {
        uint8_t i   = 0;
        char * attr = strtok(value, arrayValueSeparator);

        while (attr != NULL && i < CONFIG_DIFICULTY_STEPS_COUNT) {
            uint16_t step = strtol(attr, &endptr, 10);
            attr          = strtok(NULL, arrayValueSeparator);

            globalConfig.difficulty.steps[i] = step;
            i++;
        }
    }
}

void Config_load(void) {
    FRESULT result = SDCard_mount("/");

    if (result != FR_OK) {
        return;
    }

    if (!SDCard_pathExists(CONFIG_GLOBAL_PATH)) {
        SDCard_createFile(CONFIG_GLOBAL_PATH);
        SDCard_unmount("/");

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
}

Config_Global * Config_get(void) {
    return &globalConfig;
}