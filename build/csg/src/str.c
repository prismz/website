#include "str.h"
#include "mem.h"
#include "util.h"

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

/* allocate size, and create and return a formatted string. */
char*
xsnprintf(size_t size, char* format, ...)
{
    va_list vl;
    va_start(vl, format);

    char* str = smalloc(sizeof(char) * size);
    vsnprintf(str, size, format, vl);

    va_end(vl);

    return str;
}

int
xstrstw(char* haystack, char* needle)
{
    if (strlen(needle) > strlen(haystack))
        return 0;

    for (size_t i = 0; i < strlen(needle); i++)
        if (haystack[i] != needle[i])
            return 0;

    return 1;
}

char*
xstrdup(char* src)
{
    char* dest = smalloc(sizeof(char) * (strlen(src) + 1));
    strcpy(dest, src);
    return dest;
}