#ifndef __SD_CARD_H_
#define __SD_CARD_H_

#include "fatfs.h"
#include "macros.h"
#include "stdio.h"
#include "string.h"

#define SDCARD_END_OF_SCAN(fileInfo) (fileInfo.fname[0] == 0)
#define SDCARD_IS_DIRECTORY(fileInfo) (fileInfo.fattrib & AM_DIR)

#define SDCARD_DIR_PAGE_SIZE 10
#define SDCARD_CONTENT_PAGE_SIZE 10
#define SDCARD_MAX_FILE_NAME_SIZE _MAX_LFN
#define SDCARD_MAX_FILE_EXTENSION_SIZE 8

typedef enum SDCard_DirReadMode {
    SDCARD_DIR_READMODE_ALL = 0,
    SDCARD_DIR_READMODE_ONLY_FILES = 1,
    SDCARD_DIR_READMODE_ONLY_DIRECTORIES = 2
} SDCard_DirReadMode;

typedef struct SDCard_Capacity {
    uint32_t total;
    uint32_t used;
    uint32_t free;
} SDCard_Capacity;

typedef struct SDCard_DirectoryStatistics {
    uint32_t files;
    uint32_t fileSizes;
    uint32_t folders;
} SDCard_DirectoryStatistics;

typedef struct SDCard_FileStatistics {
    uint32_t size;
    uint32_t lines;
} SDCard_FileStatistics;

typedef struct SDCard_SearchResult {
    uint32_t count;
    uint32_t *indexes;
} SDCard_SearchResult;

typedef struct SDCard_FSItem {
    uint8_t directory;
    char name[SDCARD_MAX_FILE_NAME_SIZE];
    uint32_t size;
    char extension[SDCARD_MAX_FILE_EXTENSION_SIZE];
} SDCard_FSItem;

typedef struct SDCard_DirPage {
    SDCard_DirReadMode readMode;
    SDCard_FSItem items[SDCARD_DIR_PAGE_SIZE];
    uint32_t startIndex;
    uint8_t resultSize;
    uint8_t endOfDir;
} SDCard_DirPage;

typedef struct SDCard_LinesPage {
    char *lines[SDCARD_CONTENT_PAGE_SIZE];
    uint32_t startIndex;
    uint8_t resultSize;
    uint8_t endOfFile;
} SDCard_LinesPage;

extern void SDCard_handleError(FRESULT result, char *message);

// Basic functions
FRESULT SDCard_mount(const char *path);
FRESULT SDCard_unmount(const char *path);
FRESULT SDCard_checkCapacity(SDCard_Capacity *capacity);
uint8_t SDCard_pathExists(char *path);
FRESULT SDCard_createDirectory(char *name);
FRESULT SDCard_createFile(char *name);
FRESULT SDCard_removeFile(char *name);
FRESULT SDCard_removeFiles(void);
FRESULT SDCard_readFile(char *name, char *readBuffer, uint32_t readLength);
FRESULT SDCard_writeFile(char *name, char *data);
FRESULT SDCard_appendFile(char *name, char *data);

// Advanced functions
FRESULT SDCard_readDirectory(char *dirPath, SDCard_DirPage *dirPage);
FRESULT SDCard_fileStatistics(char *fileName, SDCard_FileStatistics *statistics);
FRESULT SDCard_directoryStatistics(char *dirPath, SDCard_DirectoryStatistics *statistics);
FRESULT SDCard_readLine(char *fileName, char *readBuffer, uint32_t lineNumber);
FRESULT SDCard_readLines(char *name, SDCard_LinesPage *page);
FRESULT SDCard_searchInFile(char *name, char *data, SDCard_SearchResult *result);

#endif