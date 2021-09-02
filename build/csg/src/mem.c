#include "mem.h"
#include "util.h"

#include <stdio.h>
#include <stdlib.h>

void* 
smalloc(size_t size)
{
    void* mem = malloc(size);
    if (mem == NULL)
        die("csg: fatal: malloc() failed.\n");
    
    return mem;
}

void* 
scalloc(size_t size)
{
    void* mem = calloc(1, size);
    if (mem == NULL)
        die("csg: fatal: calloc() failed.\n");
    
    return mem;
}

void* 
srealloc(void* ptr, size_t size)
{
    void* mem = realloc(ptr, size);
    if (mem == NULL)
        die("csg: fatal: realloc() failed.\n");
    
    return mem;
}