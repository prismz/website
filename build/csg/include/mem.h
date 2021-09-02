#ifndef CSG_MEM_H
#define CSG_MEM_H

#include <stdio.h>
#include <stdlib.h>

void* smalloc(size_t size);
void* scalloc(size_t size);
void* srealloc(void* ptr, size_t size);

#endif