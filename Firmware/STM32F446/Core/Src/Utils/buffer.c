#include "buffer.h"

uint32_t get32BitData(uint8_t * buffer, uint8_t start) {
    uint32_t data = 0;

    data |= (uint32_t)(buffer[start]) << 24;
    data |= (uint32_t)(buffer[start + 1]) << 16;
    data |= (uint32_t)(buffer[start + 2]) << 8;
    data |= (uint32_t)(buffer[start + 3]);

    return data;
}

void set32BitData(uint8_t * buffer, uint8_t start, uint32_t data) {
    buffer[start]     = (data >> 24) & 0xFF;
    buffer[start + 1] = (data >> 16) & 0xFF;
    buffer[start + 2] = (data >> 8) & 0xFF;
    buffer[start + 3] = data & 0xFF;
}