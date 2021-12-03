#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <wchar.h>
#include <locale.h>

void
die(char* fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    vfprintf(stderr, fmt, vl);
    va_end(vl);
    exit(1);
}

void*
safe_malloc(size_t size)
{
    void* mem;
    if ((mem = malloc(size)) == NULL)
        die("malloc failed.\n");

    return mem;
}

void*
safe_realloc(void* ptr, size_t size)
{
    void* mem;
    if ((mem = realloc(ptr, size)) == NULL)
        die("realloc failed.\n");

    return mem;
}

wchar_t*
read_file(char* path)
{
    FILE* fp = fopen(path, "rb");
    if (!fp) {
        fprintf(stderr, "warning: failed to read file %s\n", path);
        return NULL;
    }

    size_t allocated = 1024, added = 0;
    wchar_t* buffer = safe_malloc(sizeof(wchar_t) * allocated);
    wint_t c;
    while ((c = fgetwc(fp)) != WEOF) {
        if (added + 1 > allocated)
            buffer = safe_realloc(buffer, sizeof(wchar_t) * (allocated += 1024));
        buffer[added++] = c;
    }
    buffer[added] = '\0';
    fclose(fp);

    return buffer;
}
