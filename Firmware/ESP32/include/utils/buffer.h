
#ifndef INC_BUFFER_H_
#define INC_BUFFER_H_

#include "stdint.h"

uint32_t get32BitData(uint8_t * buffer, uint8_t start);
void set32BitData(uint8_t * buffer, uint8_t start, uint32_t data);

#endif /* INC_BUFFER_H_ */
