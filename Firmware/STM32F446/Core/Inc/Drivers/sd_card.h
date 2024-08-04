#ifndef __SD_CARD_H_
#define __SD_CARD_H_

#include "fatfs.h"
#include "stdio.h"
#include "string.h"

typedef struct SDCard_capacity {
    uint32_t total;
    uint32_t used;
    uint32_t free;
} SDCard_capacity;

FRESULT SDCard_mount(const TCHAR *path);
FRESULT SDCard_unmount(const TCHAR *path);
FRESULT SDCard_checkCapacity(SDCard_capacity *capacity);
FRESULT SDCard_removeFiles(void);
FRESULT SDCard_writeFile(char *name, char *data);
FRESULT SDCard_readFile(char *name);
FRESULT SDCard_createFile(char *name);
FRESULT SDCard_removeFile(char *name);
FRESULT SDCard_createDirectory(char *name);
FRESULT SDCard_updateFile(char *name, char *data);

FRESULT SDCard_writeLine(char *fileName, char *line);

#endif