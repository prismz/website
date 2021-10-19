#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "config.h"

#define NLOWER  "0123456789"             \
                "ABCDEFGHIJK"            \
                "LMNOPQRSTUV"            \
                "WXYZ!\"#$%%&"           \
                "()*+,-./:;<'"           \
                "=>?@[\\]^_`{"           \
                "|}~ \t\n\r\x0b\x0c"

struct metadata {
    char** sections;
    char* raw_body;
    char* content_list;
    size_t nsections;
    size_t content_added;
};

void
init_metadata(struct metadata* m)
{
    m->sections = malloc(sizeof(char*) * 1);
    m->raw_body = malloc(sizeof(char) * 1);
    m->content_list = strdup(content_list_header);
    m->content_added = 0;
    m->nsections = 0;
}

void
free_metadata(struct metadata* m)
{
    for (size_t i = 0; i < m->nsections; i++)
        free(m->sections[i]);
    free(m->sections);
    free(m->raw_body);
    free(m->content_list);
    m->content_added = 0;
    m->nsections = 0;
}

char*
read_file(char* path)
{
    FILE* fp = fopen(path, "rb");
    if (!fp)
        return NULL;

    size_t added = 0;
    size_t allocated = 1024;
    char* buff = calloc(1, sizeof(char) * allocated);
    char* linebuffer = malloc(sizeof(char) * 1024);
    while (fgets(linebuffer, 1024, fp) != NULL) {
        if (added + sizeof(buff) > allocated - 5)
            buff = realloc(buff, sizeof(char) * (allocated *= 2));

        added += sizeof(buff);
        strcat(buff, linebuffer);
    }

    fclose(fp);
    free(linebuffer);
    
    return buff;
}

/* check if a string starts with another string */
int
strstw(char* haystack, char* needle)
{
    size_t hl = strlen(haystack);
    size_t nl = strlen(needle);
    if (nl > hl)
        return 0;

    for (size_t i = 0; i < nl; i++) {
        if (haystack[i] != needle[i])
            return 0;
    }

    return 1;
}

/*
 * check if a string starts with another string,
 * ignore leading and trailing whitespace
 */
int
strstw_w(char* haystack, char* needle)
{

}

/*
 * yank the body of an html tag
 * ex:
 * yank_tag("<h4>title</h4>") -> "title"
 */
char*
yank_tag(char* str)
{
    char* body = malloc(sizeof(char) * (strlen(str) + 1));
    if (body == NULL)
        return NULL;
}

int
char_in_str(char* str, char c)
{
    for (size_t i = 0; i < strlen(str); i++)
        if (str[i] == c)
            return 1;
    
    return 0;
}

char*
xsnprintf(size_t n, char* fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    char* str = malloc(sizeof(char) * n);
    if (str == NULL)
        return NULL;

    vsnprintf(str, n, fmt, vl);;
    va_end(vl);
    
    return str;
}

char*
str_to_id(char* str)
{
    char* nstr = strdup(str);
    char* istr = strdup(str);
    if (nstr == NULL)
        return NULL;

    size_t i, j = 0, k;
    for (i = 0; i < strlen(nstr); i++) {
        char c = str[i];

        /* convert to lowercase */
        if (c >= 'A' && c <= 'Z')
            c -= ('A' - 'a');
        
        if (!char_in_str(NLOWER, c) || c == ' ')
            if (c == ' ' && str[i - 1] != ' ')  /* no extra spaces */
                istr[j++] = '_';
            else if (c != ' ')
                istr[j++] = c;
    }

    /* remove trailing spaces */
    for (k = j-1; k >= 0; k--)
        if (istr[k] == '_')
            j--;
        else
            break;

    istr = realloc(istr, sizeof(char) * (j+1));  /* resize */
    istr[j] = '\0';
    free(nstr);
    return istr;
}

int
parse_article(char* path)
{
    char* c = read_file(path);
    if (c == NULL)
        return 1;

    struct metadata m;
    init_metadata(&m);

    for (char* ptr = strtok(c, "\n"); ptr != NULL; ptr = strtok(NULL, "\n")) {
        if (strstw_w(ptr, SECTION_HEADER)) {
            char* title = yank_tag(ptr);
            char* id = str_to_id(title);
        }
    }

    free_metadata(&m);
    return 0;
}

int
main()
{
    str_to_id("ABCdef()       a             234__\\%%");
}