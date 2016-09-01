
#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

long size(char *filename);
void read(char *filename, uint32_t *content);
void print(uint32_t *array, long length);

#endif // IO_H
