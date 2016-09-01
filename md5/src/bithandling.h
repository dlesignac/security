
#ifndef BITHANDLING_H
#define BITHANDLING_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define LITTLE_ENDIAN 0
#define BIG_ENDIAN    1

uint32_t leftrotate32(uint32_t x, int n);
uint32_t swap32(uint32_t n, int x, int y);
uint32_t reverse_endian32(uint32_t n);

#endif //BITHANDLING_H

