#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#define NLOWER "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~\t\n\r\x0b\x0c"

struct article {
    char* raw_body;
    char** sections;
    char* content_list;
    int added_content;
};

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
usage(void)
{
    die("gen [src] [dst] [index_template]\n");
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

char*
strip_str(char* line)
{
    char* nline = malloc(sizeof(char) * (strlen(line) + 1));
    if (nline == NULL)
        die("malloc\n");
    
    size_t i, k;
    for (i = 0; i < strlen(line); i++) {
        if (!isspace(line[i]))
            break;
    }
    
    strcpy(nline, line + i);
    
    for (k = strlen(nline) - 1; (long long)k >= 0; k--) {
        if (isspace(nline[k]))
            nline[k] = '\0';
        else
            break;
    }

    return nline;
}

char*
title_to_id(char* title)
{
    char* id = malloc(sizeof(char) * (strlen(title) + 1));
    if (id == NULL)
        die("malloc\n");

    size_t k = 0;
    for (size_t i = 0; i < strlen(title); i++) {
        if (title[i] >= 'A' && title[i] <= 'Z')
            title[i] -= 'A';

        if (!strstr(NLOWER, (char[2]){ title[i], '\0'})) {
            if (title[i] != ' ')
                id[k++] = title[i];
            else
                id[k++] = '_';
        }
    }
    id[k] = '\0';

    return id;
}

struct article*
parse_article(char* path)
{
    char* raw_contents = read_file(path);
    char* dup = strdup(raw_contents);
    char* line = strtok(dup, "\n");
    while (line != NULL) {
        char* stripped = strip_str(line); 
        if (!strncmp(stripped, "<h4>", strlen("<h4>"))) {  /* <h4> is reserved for tags */
            char* title = stripped + strlen("<h4>");
            title[strlen(title) - 2 - strlen("<h4")] = '\0';

            char* id = title_to_id(title);
            char* nline = malloc(sizeof(char) * (strlen(title) * 2 + 20));
            if (nline == NULL)
                die("malloc\n");
            snprintf(nline, strlen(title) * 2 + 20, "<h4 id=\"%s\">%s</h4>", id, title);

            printf("%s: %s\n", title, id);
            free(id);
            free(nline);
        }

        free(stripped);
        line = strtok(NULL, "\n");
    }

    free(dup);

    return NULL;
}

int
main(int argc, char** argv)
{
    if (argc <= 3)
        usage();

    char* src = argv[1];  /* src directory */
    char* dst = argv[2];  /* dest directory */
    char* itp = argv[3];  /* index template */
    struct article* a = parse_article("../c/gentootips.html");
}
