#ifndef __MY_MALLOC_H
#define __MY_MALLOC_H

#define HEADER_SIZE (sizeof(block_t*)+sizeof(block_t*)+sizeof(char))

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void *my_malloc(size_t size);
void my_free(void *ptr);

#endif