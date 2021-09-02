#ifndef CSG_UTIL_H
#define CSG_UTIL_H

#include <stdarg.h>

void die(char* format, ...);
char* read_file(char* path);
char* path_basename(char* path);
int dir_exists(char* path);
int write_file(char* file, char* str);

#endif