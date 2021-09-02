#include "util.h"
#include "mem.h"
#include "str.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>

void
die(char* format, ...)
{
    va_list vl;
    va_start(vl, format);

    vfprintf(stderr, format, vl);

    va_end(vl);

    exit(EXIT_FAILURE);
}

char*
read_file(char* path)
{
    FILE* fp = fopen(path, "rb");
    if (!fp)
        return NULL;

    size_t copied = 0;
    size_t csz = 2048;

    char* dest = scalloc(sizeof(char) * csz);
    char* cb = scalloc(sizeof(char) * csz);
    while (fgets(cb, 2048, fp) != NULL) {
        if (copied + strlen(cb) + 10 > csz)
            dest = srealloc(dest, csz *= 2);
        strcat(dest, cb);
        copied += strlen(cb);
    }

    free(cb);
    fclose(fp);
    
    return dest;
}

char*
path_basename(char* path)
{
    char* str = xstrdup(path);
    size_t si = 0;
    for (size_t i = 0; i < strlen(path); i++) {
        if (path[i] == '/' && i != strlen(path)-1) {
            strcpy(str, "");
            si = 0;
        } else {
            str[si] = path[i];
            str[si + 1] = '\0';
            si++;
        }
    }
    return str;
}

int
dir_exists(char* path)
{
    DIR* dir = opendir(path);
    if (!dir) 
        return 0;
    
    closedir(dir);
    return 1;
}

int
write_file(char* file, char* str)
{
    FILE* fp = fopen(file, "wb+");
    if (!fp)
        return 1;
    
    int rc = fprintf(fp, "%s", str);
    fclose(fp);
    if (rc < 0)
        return 1;

    return 0;
}