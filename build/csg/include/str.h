#ifndef CSG_STR_H
#define CSG_STR_H

#include <stdlib.h>

char* xsnprintf(size_t size, char* format, ...);
int xstrstw(char* haystack, char* needle);
char* xstrdup(char* src);

#endif