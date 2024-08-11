#include "sd_card.h"

FATFS fs;  // file system
FATFS *pfs;

const char *newLine = "\n";

PRIVATE void handleError(FRESULT result, char *message) {
#ifdef SD_CARD_DEBUG
    SDCard_handleError(result, message);
#endif
}

PRIVATE void handleErrorWithParam(FRESULT result, char *message, char *param) {
#ifdef SD_CARD_DEBUG
    char *buf = malloc(100 * sizeof(char));
    sprintf(buf, message, param);
    SDCard_handleError(result, buf);
    free(buf);
#endif
}

FRESULT SDCard_mount(const char *path) {
    FRESULT result = f_mount(&fs, path, 1);

    if (result != FR_OK) {
        handleError(result, "Couldn't mount filesystem!");
    }

    return result;
}

FRESULT SDCard_unmount(const char *path) {
    FRESULT result = f_mount(NULL, path, 1);

    if (result != FR_OK) {
        handleError(result, "Couldn't unmount filesystem!");
    }

    return result;
}

FRESULT SDCard_checkCapacity(SDCard_Capacity *capacity) {
    DWORD fre_clust;
    FRESULT result = f_getfree("", &fre_clust, &pfs);

    if (result == FR_OK) {
        uint32_t total_capacity = (uint32_t)((pfs->n_fatent - 2) * pfs->csize * 0.5);
        uint32_t free_space = (uint32_t)(fre_clust * pfs->csize * 0.5);
        uint32_t used_space = total_capacity - free_space;

        capacity->total = total_capacity;
        capacity->free = free_space;
        capacity->used = used_space;
    } else {
        handleError(result, "Couldn't load capacity details!");
    }

    return result;
}

FRESULT SDCard_createDirectory(char *name) {
    FRESULT result = f_mkdir(name);

    return result;
}

FRESULT SDCard_createFile(char *name) {
    FIL file;
    FILINFO fileInfo;
    FRESULT result = f_stat(name, &fileInfo);

    if (result == FR_OK) {
        handleErrorWithParam(FR_EXIST, "File '%s' already exists!", name);

        return FR_EXIST;
    }

    result = f_open(&file, name, FA_CREATE_ALWAYS | FA_READ | FA_WRITE);

    if (result != FR_OK) {
        handleErrorWithParam(result, "File '%s' cannot be opened!", name);

        return result;
    }

    result = f_close(&file);

    if (result != FR_OK) {
        handleErrorWithParam(result, "File '%s' cannot be closed!", name);
    }

    return result;
}

FRESULT SDCard_removeFile(char *name) {
    FILINFO fileInfo;
    /**** check whether the file exists or not ****/
    FRESULT result = f_stat(name, &fileInfo);

    if (result != FR_OK) {
        return result;
    } else {
        result = f_unlink(name);
    }

    return result;
}

FRESULT SDCard_removeFiles(void) {
    DIR dir;
    FILINFO fileInfo;
    char *path = malloc(20 * sizeof(char));
    sprintf(path, "%s", "/");

    FRESULT result = f_opendir(&dir, path);

    free(path);

    if (result != FR_OK) {
        handleError(result, "Couldn't open root directory!");

        return result;
    }

    while (1) {
        result = f_readdir(&dir, &fileInfo);

        if (result != FR_OK || fileInfo.fname[0] == 0) {
            handleError(result, "Couldn't read file or directory in the root filesystem!");
            break;
        }

        if (SDCARD_IS_DIRECTORY(fileInfo)) {
            if (!(strcmp("SYSTEM~1", fileInfo.fname))) {
                continue;
            }

            result = f_unlink(fileInfo.fname);
        } else { /* It is a file. */
            result = f_unlink(fileInfo.fname);
        }

        if (result != FR_OK) {
            handleErrorWithParam(result, "File/Directory '%s' cannot be deleted!", fileInfo.fname);
        }
    }

    result = f_closedir(&dir);

    if (result != FR_OK) {
        handleError(result, "Couldn't close root directory!");
    }

    return result;
}

FRESULT SDCard_readFile(char *name, char *readBuffer, uint32_t readLength) {
    FIL file;
    FILINFO fileInfo;
    UINT bytesRead;

    FRESULT result = f_stat(name, &fileInfo);

    if (result != FR_OK) {
        handleErrorWithParam(result, "File '%s' doesn't exist!", name);

        return result;
    }

    result = f_open(&file, name, FA_READ);

    if (result != FR_OK) {
        handleErrorWithParam(result, "File '%s' cannot be opened!", name);

        return result;
    }

    result = f_read(&file, readBuffer, readLength, &bytesRead);

    if (result != FR_OK) {
        handleErrorWithParam(result, "Couldn't read from file '%s'!", name);
    }

    result = f_close(&file);

    if (result != FR_OK) {
        handleErrorWithParam(result, "File '%s' cannot be closed!", name);
    }

    return result;
}

FRESULT SDCard_writeFile(char *name, char *data) {
    FIL file;
    FILINFO fileInfo;
    UINT bytesWritten;

    FRESULT result = f_stat(name, &fileInfo);

    if (result != FR_OK) {
        handleErrorWithParam(result, "File '%s' does not exists!", name);

        return result;
    }

    result = f_open(&file, name, FA_OPEN_EXISTING | FA_WRITE);

    if (result != FR_OK) {
        handleErrorWithParam(result, "File '%s' cannot be opened!", name);

        return result;
    }

    result = f_write(&file, data, strlen(data), &bytesWritten);

    if (result != FR_OK) {
        handleErrorWithParam(result, "Couldn't write into file '%s'!", name);
    }

    result = f_close(&file);

    if (result != FR_OK) {
        handleErrorWithParam(result, "File '%s' cannot be closed!", name);
    }

    return result;
}

FRESULT SDCard_appendFile(char *name, char *data) {
    FIL file;
    FILINFO fileInfo;
    UINT bytesWritten;

    FRESULT result = f_stat(name, &fileInfo);

    if (result != FR_OK) {
        handleErrorWithParam(result, "File '%s' doesn't exist!", name);

        return result;
    }

    result = f_open(&file, name, FA_OPEN_APPEND | FA_WRITE);

    if (result != FR_OK) {
        handleErrorWithParam(result, "File '%s' cannot be opened!", name);

        return result;
    }

    result = f_write(&file, data, strlen(data), &bytesWritten);

    if (result != FR_OK) {
        handleErrorWithParam(result, "Couldn't write to file '%s'!", name);
    }

    result = f_close(&file);

    if (result != FR_OK) {
        handleErrorWithParam(result, "File '%s' cannot be closed!", name);
    }

    return result;
}

/**
 * Advanced functions
 */

FRESULT SDCard_fileStatistics(char *name, SDCard_FileStatistics *statistics) {
    FIL file;
    FILINFO fileInfo;
    FRESULT result;

    result = f_stat(name, &fileInfo);

    if (result != FR_OK) {
        handleErrorWithParam(result, "File '%s' doesn't exist!", name);

        return result;
    }

    result = f_open(&file, name, FA_READ);

    if (result != FR_OK) {
        handleErrorWithParam(result, "File '%s' cannot be opened!", name);

        return result;
    }

    uint32_t lineCount = 0;
    uint8_t bufferSize = 32;
    UINT bytesRead = bufferSize;
    char readBuffer[bufferSize];
    char *searchBuffer;

    while (bytesRead == bufferSize) {
        result = f_read(&file, readBuffer, bufferSize, &bytesRead);

        if (result != FR_OK) {
            handleErrorWithParam(result, "Couldn't read from file '%s'!", name);
            break;
        }

        searchBuffer = readBuffer;

        while ((searchBuffer = strstr(searchBuffer, newLine))) {
            lineCount++;
            searchBuffer += strlen(newLine);
        }
    }

    statistics->size = fileInfo.fsize;
    statistics->lines = lineCount + 1;

    return result;
}

FRESULT SDCard_appendLine(char *name, char *writeBuffer) {
    FRESULT result;

    result = SDCard_mount("/");

    if (result != FR_OK) {
        return result;
    }

    result = SDCard_createFile(name);

    if (result != FR_OK) {
        return result;
    }

    result = SDCard_writeFile(name, writeBuffer);

    if (result != FR_OK) {
        return result;
    }

    result = SDCard_unmount("/");

    return result;
}

FRESULT SDCard_readLine(char *name, char *resultBuffer, uint32_t lineNumber) {
    FIL file;
    FILINFO fileInfo;
    FRESULT result;

    result = f_stat(name, &fileInfo);

    if (result != FR_OK) {
        handleErrorWithParam(result, "File '%s' doesn't exist!", name);

        return result;
    }

    result = f_open(&file, name, FA_READ);

    if (result != FR_OK) {
        handleErrorWithParam(result, "File '%s' cannot be opened!", name);

        return result;
    }

    uint32_t lineCount = 0;
    uint32_t lineCurPos = 0, lineStartPos = 0, lineEndPos = 0;
    uint8_t bufferSize = 4;
    UINT bytesRead = bufferSize;
    uint8_t found = 0;
    char readBuffer[bufferSize];
    char *searchBuffer;

    while (bytesRead == bufferSize) {
        result = f_read(&file, readBuffer, bufferSize, &bytesRead);

        if (result != FR_OK) {
            handleErrorWithParam(result, "Couldn't read from file '%s'!", name);
            break;
        }

        searchBuffer = readBuffer;

        while ((searchBuffer = strstr(searchBuffer, newLine))) {
            uint8_t lineSubPos = (uint8_t)(searchBuffer - readBuffer);

            if (lineNumber > 0 && lineStartPos == 0 && lineNumber - 1 == lineCount) {
                lineStartPos = lineCurPos + lineSubPos + 1;
            } else if (lineNumber == 0 || lineStartPos > 0) {
                lineEndPos = lineCurPos + lineSubPos;
                found = 1;
                break;
            }

            lineCount++;

            searchBuffer += strlen(newLine);
        }

        if (found) {
            break;
        }

        lineCurPos += bufferSize;
    }

    if (lineStartPos != lineEndPos) {
        f_lseek(&file, lineStartPos);
        f_read(&file, resultBuffer, lineEndPos - lineStartPos, &bytesRead);
    }

    return result;
}

FRESULT SDCard_searchInFile(char *name, char *data, SDCard_SearchResult *result) {
    // TODO: Implement
    return FR_OK;
}