#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>

#include "config.h"

#define NLOWER  "0123456789"             \
                "ABCDEFGHIJK"            \
                "LMNOPQRSTUV"            \
                "WXYZ!\"#$%%&"           \
                "()*+,-./:;<'"           \
                "=>?@[\\]^_`{"           \
                "|}~ \t\n\r\x0b\x0c"
#define ISNULL(x) (x == NULL) ? 1 : 0

struct metadata {
    char* title;
    char* raw_body;
    char* content_list;
    char* category;
    size_t content_added;
    int parsed;
};

void
init_metadata(struct metadata* m)
{
    m->raw_body = malloc(sizeof(char) * 1);
    m->content_list = strdup(content_list_header);
    m->title = NULL;
    m->category = NULL;
    m->content_added = 0;
    m->parsed = 0;
}

void
free_metadata(struct metadata* m)
{
    free(m->category);
    free(m->title);
    free(m->raw_body);
    free(m->content_list);
    m->content_added = 0;
    m->parsed = 0;
}

char*
read_file(char* path)
{
    FILE* fp = fopen(path, "rb");
    if (!fp)
        return NULL;

    size_t allocated = 1024, i = 0;
    char* buffer = malloc(sizeof(char) * allocated);
    char c;
    while ((c = fgetc(fp)) != EOF) {
        if (i + 1 > allocated)
            buffer = realloc(buffer, allocated += 512);
        
        buffer[i++] = c;
    }

    buffer[i] = '\0';
   
    fclose(fp);

    return buffer;
}

int
write_file(char* filename, char* content)
{
    FILE* fp = fopen(filename, "wb+");
    if (!fp)
        return 1;

    fprintf(fp, "%s", content);
    fclose(fp);
    return 0;
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
        if (needle[i] != haystack[i])
            return 0;
    }

    return 1;
}

/*
 * yank the body of an html tag
 * ex:
 * yank_tag("<h4>title</h4>") -> "title"
 */
char*
yank_tag(char* str)
{
    int bi = 0;
    char* body = malloc(sizeof(char) * (strlen(str) + 1));
    if (body == NULL)
        return NULL;

    int beg = 0;
    for (size_t i = 0; i < strlen(str); i++) {
        if (str[i] == '>')
            beg = 1;
        else if (beg) {
            if (str[i] == '<')
                break;
            body[bi++] = str[i];
        }
    }
    body[bi] = '\0';

    return body;
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
xsnprintf(size_t n, const char* fmt, ...)
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
        if (c >= 'A' && c <= 'Z') {
            c -= ('A' - 'a');
        }

        if (!char_in_str(NLOWER, c) || c == ' ') {
            if (c == ' ' && str[i - 1] != ' ')  /* no extra spaces */
                istr[j++] = '_';
            else if (c != ' ')
                istr[j++] = c;
        }
    }

    /* remove trailing spaces */
    for (k = j - 1; (long long)k >= 0; k--)
        if (istr[k] == '_')
            j--;
        else
            break;

    istr = realloc(istr, sizeof(char) * (j + 1));  /* resize */
    istr[j] = '\0';
    free(nstr);

    return istr;
}

struct metadata
parse_article(char* path)
{
    printf("beginning to parse article %s.\n", path);
    struct metadata m;
    init_metadata(&m);
    char* c = read_file(path);
    if (c == NULL) {
        printf("parse_article failed: %s\n", path);
        return m;
    }
    size_t raw_size = strlen(c) * 2;
    int have_content = 0;
    free(m.raw_body);
    m.raw_body = calloc(1, raw_size);

    for (char* ptr = strtok(c, "\n"); ptr != NULL; ptr = strtok(NULL, "\n")) {
        if (strstw(ptr, TITLE_HEADER)) {
            char* title = yank_tag(ptr);
            m.title = title;
            printf("title: %s\n", title);
            continue;
        } else if (strstw(ptr, SECTION_HEADER)) {
            char* title = yank_tag(ptr);
            char* id = str_to_id(title);
            size_t fmt_size = strlen(id) + (strlen(title) * 2) + 512;

            char* fmt_title = xsnprintf(fmt_size,
                "<h4 id=\"%s\">%s [<a href=\"#%s\"></a>]</h4>\n",
                id, title, id);

            char* fmt_id_item = xsnprintf(fmt_size,
                "    <li class=\"secl-item\">%zu. <a href=\"#%s\">%s</a></li>\n",
                m.content_added + 1, id, title);

            m.content_list = realloc(m.content_list, strlen(m.content_list) + strlen(fmt_id_item) + 256);
            m.content_added++;

            printf("section: %s\n", title);
            strcat(m.raw_body, fmt_title);
            strcat(m.content_list, fmt_id_item);
            free(fmt_title);
            free(fmt_id_item);
            free(title);
            free(id);

            have_content = 1;
            continue;
        } else {
            strcat(m.raw_body, ptr);
        }
    }
    strcat(m.content_list, "</ul><br>\n\n");
    printf("finished building...\n");
    printf("%d %d %d %d\n", ISNULL(m.content_list), ISNULL(m.raw_body), ISNULL(m.title), have_content);
    size_t size = strlen(m.title) + (have_content ? strlen(m.content_list) : 10) + strlen(m.raw_body) + 256;
    printf("got size %d...\n", (int)size);

    printf("beginning...\n");

    printf("print...\n");
    // char* nbody = xsnprintf(
    //     size,
    //     "<h3>%s</h3>\n%s\n%s",
    //     m.title, ((have_content) ? m.content_list : "\n"), m.raw_body);

    printf("copy...\n");
    // free(m.raw_body);
    // free(c);

    // m.raw_body = nbody;
    m.parsed = 1;
    printf("set...\n");

    return m;
}

char*
format_article(struct metadata* m, char* header, char* footer, char* stylepath)
{
    if (!m->parsed) {
        printf("no metadata passed to format_article.\n");
        return NULL;
    }

    char* raw = m->raw_body;
    char* title = m->title;
    char* ftitle = xsnprintf(strlen(title) + 512,
        "%s - hasan zahra's website",
        title);
    
    char* rhh = xsnprintf(strlen(html_header) + strlen(ftitle) + 512,
        html_header, ftitle, stylepath);
    
    char* hbf = xsnprintf(strlen(header) + 
        strlen(footer) + strlen(raw) + 256,
        "%s\n%s\n%s", header, raw, footer);

    char* bb = xsnprintf(
        strlen(html_boiler_body) + strlen(hbf) + 256,
        html_boiler_body, hbf);
    
    char* rhbb = xsnprintf(strlen(rhh) + strlen(bb) + 256,
        "%s%s", rhh, bb);
    
    char* full = xsnprintf(strlen(rhh) + strlen(bb) + 256,
        html_boiler_head, rhbb);
    
    free(ftitle);
    free(rhh);
    free(hbf);
    free(bb);
    free(rhbb);

    return full;
}

int
parse_article_dir(char* srcdir, char* dstdir)
{
    DIR* dir = opendir(srcdir);
    DIR* subdir;
    if (!dir)
        return 1;

    struct dirent* ent, *subent;
    while ((ent = readdir(dir)) != NULL) {
        char* dname = ent->d_name;
        if (!strcmp(dname, ".") || !strcmp(dname, ".."))
            continue;
        // printf("%s\n", ent->d_name);
        char* dpath = xsnprintf(PATH_MAX, "%s/%s", srcdir, ent->d_name);
        subdir = opendir(dpath);
        if (!subdir)
            continue;
        while ((subent = readdir(subdir)) != NULL) {
            char* sdname = subent->d_name;
            if (!strcmp(sdname, ".") || !strcmp(sdname, ".."))
                continue;
            
            char* article_path = xsnprintf(PATH_MAX, "%s/%s", dpath, sdname);
            printf("%s\n", article_path);
            struct metadata m = parse_article(article_path);
            printf("made...\n");
            free(article_path);
            free_metadata(&m);
            printf("free...\n");
        }
        free(dpath);
    }

    printf("complete...\n");
    return 0;
}


// int
// generate(char* srcdir, char* dstdir)
// {

// }

int
main(void)
{
    char* header = read_file("../u/header.html");
    char* footer = read_file("../u/footer.html");
    if (header == NULL || footer == NULL) {
        printf("err head/foot\n");
        return 1;
    }

    parse_article_dir("../c", "../d");
    free(header);
    free(footer);
}