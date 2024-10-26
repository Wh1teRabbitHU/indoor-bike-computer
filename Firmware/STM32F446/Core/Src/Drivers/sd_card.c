#include "sd_card.h"

FATFS fs;  // file system
FATFS *pfs;

const char *folderSeparator = "/";
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

PRIVATE void storeFileExtension(const char *fileName, char *extension) {}

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

uint8_t SDCard_pathExists(char *path) {
    FILINFO fileInfo;
    FRESULT result = f_stat(path, &fileInfo);

    return result == FR_OK ? 1 : 0;
}

FRESULT SDCard_createDirectory(char *name) {
    FRESULT result = FR_OK;
    char buffer[SDCARD_MAX_FILE_NAME_SIZE] = {0};
    char pathBuffer[SDCARD_MAX_FILE_NAME_SIZE] = {0};

    strcpy(buffer, name);
    char *folder = strtok(buffer, folderSeparator);

    while (folder != NULL) {
        strcat(pathBuffer, "/");
        strcat(pathBuffer, folder);

        result = f_mkdir(pathBuffer);

        if (result != FR_OK && result != FR_EXIST) {
            return result;
        }

        folder = strtok(NULL, folderSeparator);
    }

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
        result = SDCard_createFile(name);

        if (result != FR_OK) {
            return result;
        }
    }

    result = f_open(&file, name, FA_CREATE_ALWAYS | FA_WRITE);

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
    UINT bytesWritten;
    FRESULT result;

    uint8_t fileExists = SDCard_pathExists(name);

    if (!fileExists) {
        SDCard_createFile(name);
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

FRESULT SDCard_readDirectory(char *dirPath, SDCard_DirPage *dirPage) {
    DIR dir;
    FILINFO fileInfo;
    FRESULT result = f_opendir(&dir, dirPath);

    if (result != FR_OK) {
        handleErrorWithParam(result, "Couldn't open directory '%s'!", dirPath);

        return result;
    }

    dirPage->endOfDir = 0;
    dirPage->resultSize = 0;

    // Move the pointer to the start of the page
    for (uint8_t i = 0; i < dirPage->startIndex; i++) {
        result = f_readdir(&dir, &fileInfo);
        uint8_t isDir = SDCARD_IS_DIRECTORY(fileInfo);

        // Skip if readmode limits the read items
        if ((dirPage->readMode == SDCARD_DIR_READMODE_ONLY_FILES && isDir) ||
            (dirPage->readMode == SDCARD_DIR_READMODE_ONLY_DIRECTORIES && !isDir)) {
            i--;
        }

        if (result != FR_OK) {
            handleError(result, "Error reading file on the storage!");
            result = f_closedir(&dir);

            return result;
        } else if (SDCARD_END_OF_SCAN(fileInfo)) {
            dirPage->endOfDir = 1;

            result = f_closedir(&dir);

            return result;
        }
    }

    for (uint8_t i = 0; i < SDCARD_DIR_PAGE_SIZE; i++) {
        result = f_readdir(&dir, &fileInfo);

        if (result != FR_OK) {
            handleError(result, "Error reading file on the storage!");
            break;
        } else if (SDCARD_END_OF_SCAN(fileInfo)) {
            dirPage->endOfDir = 1;
            break;
        }

        uint8_t isDir = SDCARD_IS_DIRECTORY(fileInfo);

        // Skip if readmode limits the read items
        if ((dirPage->readMode == SDCARD_DIR_READMODE_ONLY_FILES && isDir) ||
            (dirPage->readMode == SDCARD_DIR_READMODE_ONLY_DIRECTORIES && !isDir)) {
            i--;
            continue;
        }

        SDCard_FSItem *item = &dirPage->items[i];

        item->directory = isDir > 0 ? 1 : 0;
        item->size = fileInfo.fsize;

        strcpy(item->name, fileInfo.fname);
        storeFileExtension(fileInfo.fname, item->extension);

        dirPage->resultSize++;
    }

    result = f_closedir(&dir);

    if (result != FR_OK) {
        handleError(result, "Couldn't close root directory!");
    }

    return result;
}

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
    statistics->lines = lineCount == 0 && bytesRead > 0 ? 1 : lineCount;

    return result;
}

FRESULT SDCard_directoryStatistics(char *dirPath, SDCard_DirectoryStatistics *statistics) {
    DIR dir;
    FILINFO fileInfo;
    FRESULT result = f_opendir(&dir, dirPath);

    if (result != FR_OK) {
        handleErrorWithParam(result, "Couldn't open directory '%s'!", dirPath);

        return result;
    }

    statistics->fileSizes = 0;
    statistics->files = 0;
    statistics->folders = 0;

    while (1) {
        result = f_readdir(&dir, &fileInfo);

        if (result != FR_OK) {
            handleError(result, "Error reading file on the storage!");
            break;
        } else if (SDCARD_END_OF_SCAN(fileInfo)) {
            break;
        }

        uint8_t isDir = SDCARD_IS_DIRECTORY(fileInfo);

        if (isDir) {
            statistics->folders += 1;
        } else {
            statistics->files += 1;
        }
        statistics->fileSizes += fileInfo.fsize;
    }

    result = f_closedir(&dir);

    if (result != FR_OK) {
        handleError(result, "Couldn't close directory!");
    }

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

FRESULT SDCard_readLines(char *name, SDCard_LinesPage *page) {
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

    uint32_t lineCount = 0, lineCurPos = 0, lineStartPos = 0, lineEndPos = 0;
    uint32_t lineNumber = page->startIndex;
    uint8_t bufferSize = 4, linesRead = 0, found = 0;
    UINT bytesRead = bufferSize;
    char readBuffer[bufferSize];
    char *searchBuffer;

    while (linesRead < SDCARD_CONTENT_PAGE_SIZE) {
        while (bytesRead == bufferSize) {
            result = f_read(&file, readBuffer, bufferSize, &bytesRead);

            if (result != FR_OK) {
                handleErrorWithParam(result, "Couldn't read from file '%s'!", name);
                return result;
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
            f_read(&file, page->lines[linesRead], lineEndPos - lineStartPos, &bytesRead);

            linesRead++;
        } else {
            break;
        }
    }

    return result;
}

FRESULT SDCard_searchInFile(char *name, char *data, SDCard_SearchResult *result) {
    // TODO: Implement
    return FR_OK;
}