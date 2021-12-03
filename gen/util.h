#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <wchar.h>

void die(char* fmt, ...);
void* safe_malloc(size_t size);
void* safe_realloc(void* ptr, size_t size);
wchar_t* read_file(char* path);

#endif
