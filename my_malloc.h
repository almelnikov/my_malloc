#ifndef __MY_MALLOC_H
#define __MY_MALLOC_H

#define HEADER_SIZE (sizeof(block_t*)*2+sizeof(size_t)+sizeof(long))
#define MINIMAL_BLOCK 40
#define MINIMAL_PAYLOAD (MINIMAL_BLOCK-HEADER_SIZE)
#define MY_MALLOC_ALLIGN 8

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void *my_malloc(size_t size);
void my_free(void *ptr);
void my_malloc_print();

#endif