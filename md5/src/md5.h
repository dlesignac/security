
#ifndef MD5_H
#define MD5_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <math.h>

#include "bithandling.h"
#include "io.h"

uint32_t* init(char *filename, long *size_array);
char* hash(uint32_t *message, long size_message);

#endif //MD5_H

