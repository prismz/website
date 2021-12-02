#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

void
die(char* fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    vfprintf(stderr, fmt, vl);
    va_end(vl);
    exit(1);
}

char*
read_file(char* path)
{
    FILE* fp = fopen(path, "rb");
    if (!fp) {
        fprintf(stderr, "couldn't open %s\n", path);
        return NULL;
    }
   
    size_t allocated = 1024, added = 0;
    char* buffer = malloc(sizeof(char) * allocated);
    if (buffer == NULL)
        die("malloc\n");
    int c; 
    while ((c = fgetc(fp)) != EOF) {
        if (added + 1 >= allocated - 1) {
            buffer = realloc(buffer, sizeof(char) * (allocated += 1024));
            if (buffer == NULL)
                die("realloc\n");
        }
        buffer[added++] = c;
    }
    buffer[added] = '\0';
    fclose(fp);

    return buffer;
}

int
nlead(char* str)
{
    int i;
    for (i = 0; i < (int)strlen(str) && str[i] == ' '; i++);
    return i;
}

void
convert_to_html(char* contents)
{
    char** lines = malloc(sizeof(char) * (strlen(contents) + 1));
    int li = 0, cli = 0;
    lines[0] = malloc(sizeof(char) * (strlen(contents) + 1));

    for (int i = 0; i < (int)strlen(contents); i++) {
        char c = contents[i];
        if (c == '\n') {
            lines[li][cli] = '\0';
            li++;
            cli = 0;
            lines[li] = malloc(sizeof(char) * (strlen(contents) + 1));
        } else {
            lines[li][cli++] = c;
        }
    }
    lines[li][cli] = '\0';

    int in_block = 0;
    for (int i = 0; i < li; i++) {
        if (lines[i][0] == '#') {  /* handle headers */
            int j;
            for (j = 0; j < (int)strlen(lines[i]) && lines[i][j] == '#'; j++);
            printf("<h%d>%s</h%d>\n", j, lines[i] + j + (nlead(lines[i] + j)), j);
        } else if (!in_block && lines[i][0] == ' ') { /* beginning of code */
            in_block = 1; 
            printf("<pre>\n%s\n", lines[i] + 4);
        } else if (in_block && lines[i][0] != ' ') {  /* end of code */
            printf("</pre>\n%s\n", lines[i]);
            in_block = 0;
        } else if (in_block) {
            printf("%s\n", lines[i] + 4); 
        } else {
            printf("%s\n", lines[i]);
        }
    }
}

int
main(void)
{
    char* c = read_file("doom.md");
    convert_to_html(c);
    free(c);
}
