#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

void
die(char* fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    vfprintf(stderr, fmt, vl);
    va_end(vl);
    exit(1);
}

void
make_uppercase(char* str)
{
    for (size_t i = 0; i < strlen(str); i++) {
        char c = str[i];
        if (c >= 'a' && c <= 'z')
            str[i] -= 32;
    }
}

char*
xsnprintf(size_t size, char* fmt, ...)
{
    char* buffer = malloc(sizeof(char) * size);
    if (buffer == NULL)
        die("malloc\n");

    va_list vl;
    va_start(vl, fmt);
    vsnprintf(buffer, size, fmt, vl);
    va_end(vl);

    return buffer;
}

void
usage(void)
{
    die("usage: mh [basename] [include guard (optional)]\n");
}

void
write_file(char* fname, char* contents)
{
    FILE* fp = fopen(fname, "wb+");
    if (!fp)
        die("failed to open %s.\n", fname);

    fprintf(fp, "%s", contents);
    fclose(fp);
}

int
main(int argc, char** argv)
{
    if (argc <= 1)
        usage();

    char* include_guard;
    char* basename = argv[1];
    char* upper_basename = strdup(argv[1]);  /* strdup() for make_uppercase() */
    make_uppercase(upper_basename);

    if (argc == 3)  /* custom guard */
        include_guard = strdup(argv[2]); 
    else
        include_guard = xsnprintf(1024, "%s_H", upper_basename);

    char* csource_fmt = xsnprintf(2048, 
            "#include \"%s.h\"\n", basename);
    char* cheader_fmt = xsnprintf(2048,
            "#ifndef %s\n"
            "#define %s\n"
            "\n"
            "#endif\n",
            include_guard,
            include_guard);

    char* cdst = xsnprintf(1024, "%s.c", basename);
    char* hdst = xsnprintf(1024, "%s.h", basename);

    write_file(cdst, csource_fmt);
    write_file(hdst, cheader_fmt);
 
    free(cdst);
    free(hdst);
    free(csource_fmt);
    free(cheader_fmt);
    free(upper_basename);
    return 0;
}
