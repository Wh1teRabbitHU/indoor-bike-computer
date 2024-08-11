#ifndef __SD_CARD_H_
#define __SD_CARD_H_

#include "fatfs.h"
#include "macros.h"
#include "stdio.h"
#include "string.h"

#define SDCARD_IS_DIRECTORY(fileInfo) (fileInfo.fattrib & AM_DIR)

typedef struct SDCard_Capacity {
    uint32_t total;
    uint32_t used;
    uint32_t free;
} SDCard_Capacity;

typedef struct SDCard_FileStatistics {
    uint32_t size;
    uint32_t lines;
} SDCard_FileStatistics;

typedef struct SDCard_SearchResult {
    uint32_t count;
    uint32_t *indexes;
} SDCard_SearchResult;

extern void SDCard_handleError(FRESULT result, char *message);

// Basic functions
FRESULT SDCard_mount(const char *path);
FRESULT SDCard_unmount(const char *path);
FRESULT SDCard_checkCapacity(SDCard_Capacity *capacity);
FRESULT SDCard_createDirectory(char *name);
FRESULT SDCard_createFile(char *name);
FRESULT SDCard_removeFile(char *name);
FRESULT SDCard_removeFiles(void);
FRESULT SDCard_readFile(char *name, char *readBuffer, uint32_t readLength);
FRESULT SDCard_writeFile(char *name, char *data);
FRESULT SDCard_appendFile(char *name, char *data);

// Advanced functions
FRESULT SDCard_fileStatistics(char *fileName, SDCard_FileStatistics *statistics);
FRESULT SDCard_appendLine(char *fileName, char *writeBuffer);
FRESULT SDCard_readLine(char *fileName, char *readBuffer, uint32_t lineNumber);
FRESULT SDCard_searchInFile(char *name, char *data, SDCard_SearchResult *result);

#endif