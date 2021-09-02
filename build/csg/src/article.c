#include "article.h"
#include "mem.h"
#include "util.h"
#include "str.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>

void
init_sitemap(struct sitemap* sm)
{
    sm->name = NULL;
    sm->header_path = NULL;
    sm->index_path = NULL;
    sm->style_path = NULL;
    sm->global_style_path = NULL;
    sm->header_style_path = NULL;
    sm->article_style_path = NULL;

    sm->header = NULL;
    sm->index = NULL;
    sm->style = NULL;
    sm->global_style = NULL;
    sm->header_style = NULL;
    sm->article_style = NULL;

    sm->articles = NULL;
    sm->article_count = 0;
}

void
init_article(struct article* a)
{
    a->title = NULL;
    a->date = NULL;

    a->header_path = NULL;
    a->html_path = NULL;
    a->style_path = NULL;

    a->html_header = NULL;
    a->header = NULL;
    a->html = NULL;
    a->style = NULL;

    a->formatted = NULL;
}

void
free_article(struct article* a)
{
    FREE_IF_NULL(a->title);
    FREE_IF_NULL(a->date);

    FREE_IF_NULL(a->header_path);
    FREE_IF_NULL(a->html_path);
    FREE_IF_NULL(a->style_path);

    FREE_IF_NULL(a->html_header);
    FREE_IF_NULL(a->header);
    FREE_IF_NULL(a->html);
    FREE_IF_NULL(a->style);

    FREE_IF_NULL(a->formatted);
}

void
free_sitemap(struct sitemap* sm)
{
    FREE_IF_NULL(sm->name);
    FREE_IF_NULL(sm->header_path);
    FREE_IF_NULL(sm->index_path);
    FREE_IF_NULL(sm->style_path);
    FREE_IF_NULL(sm->global_style_path);
    FREE_IF_NULL(sm->header_style_path);
    FREE_IF_NULL(sm->article_style_path);
    FREE_IF_NULL(sm->header);
    FREE_IF_NULL(sm->index);
    FREE_IF_NULL(sm->style);
    FREE_IF_NULL(sm->global_style);
    FREE_IF_NULL(sm->header_style);
    FREE_IF_NULL(sm->article_style);

    for (size_t i = 0; i < sm->article_count; i++)
        free_article(sm->articles[i]);
    FREE_IF_NULL(sm->articles);

    sm->article_count = 0;
}

int
populate_sitemap(char* srcdir, struct sitemap* sm)
{
    char* metadata_path = xsnprintf(256, "%s/index/metadata", srcdir);
    FILE* fp = fopen(metadata_path, "rb");
    if (!fp)
        return 1;

    char* cbuff = smalloc(sizeof(char) * 2048);
    while (fgets(cbuff, 2048, fp) != NULL) {
        char* cbuff_c = xstrdup(cbuff);

        /*
         * unused variable, assigned to
         * in following if statements, to prevent
         * compiler warnings.
         */
        char x;

        if (cbuff_c[strlen(cbuff_c) - 1] == '\n')
            cbuff_c[strlen(cbuff_c) - 1] = '\0';

        if (xstrstw(cbuff, "TITLE")) {
            for (size_t i = 0; i <= strlen("TITLE"); i++)
                x = *cbuff_c++;

            sm->name = xstrdup(cbuff_c);

            for (size_t i = 0; i <= strlen("TITLE"); i++)
                x = *cbuff_c--;
        }

        free(cbuff_c);

        if (x) {}  /* pointless comparison, see comment above */
    }
    fclose(fp);
    free(cbuff);
    free(metadata_path);

    sm->header_path = xsnprintf(256, "%s/header.html", srcdir);
    sm->article_style_path = xsnprintf(256, "%s/style/article.css", srcdir);
    sm->global_style_path = xsnprintf(256, "%s/style/global.css", srcdir);
    sm->header_style_path = xsnprintf(256, "%s/style/header.css", srcdir);

    sm->header = read_file(sm->header_path);
    if (sm->header == NULL)
        return 1;

    sm->article_style = read_file(sm->article_style_path);
    if (sm->article_style == NULL)
        return 1;

    sm->global_style = read_file(sm->global_style_path);
    if (sm->global_style == NULL)
        return 1;

    sm->header_style = read_file(sm->header_style_path);
    if (sm->header_style == NULL)
        return 1;

    return 0;
}

int
parse_article_metadata(char* article_dir, struct article* a)
{
    char* metadata_path = xsnprintf(256, "%s/metadata", article_dir);

    FILE* fp = fopen(metadata_path, "rb");
    if (!fp)
        return 1;

    char* cbuff = smalloc(sizeof(char) * 2048);
    while (fgets(cbuff, 2048, fp) != NULL) {
        char* cbuff_c = xstrdup(cbuff);

        /*
         * unused variable, assigned to
         * in following if statements, to prevent
         * compiler warnings.
         */
        char x;

        if (cbuff_c[strlen(cbuff_c) - 1] == '\n')
            cbuff_c[strlen(cbuff_c) - 1] = '\0';

        if (xstrstw(cbuff, "TITLE")) {
            for (size_t i = 0; i <= strlen("TITLE"); i++)
                x = *cbuff_c++;

            a->title = xstrdup(cbuff_c);

            for (size_t i = 0; i <= strlen("TITLE"); i++)
                x = *cbuff_c--;

        } if (xstrstw(cbuff, "DATE")) {
            for (size_t i = 0; i <= strlen("DATE"); i++)
                x = *cbuff_c++;

            a->date = xstrdup(cbuff_c);

            for (size_t i = 0; i <= strlen("DATE"); i++)
                x = *cbuff_c--;
        }

        free(cbuff_c);

        if (x) {}  /* pointless comparison, see comment above */
    }
    free(cbuff);
    free(metadata_path);
    fclose(fp);
    return 0;
}

int
parse_article(char* article_dir, struct article* a, struct sitemap* sm)
{
    if (parse_article_metadata(article_dir, a))
        return 1;

    char* basename = path_basename(article_dir);
    a->html_path = xsnprintf(256, "%s/%s.html", article_dir, basename);
    a->header_path = xstrdup(sm->header_path);
    free(basename);

    a->html = read_file(a->html_path);
    a->style = read_file(sm->article_style_path);
    a->header = read_file(a->header_path);

    if (a->html == NULL || a->style == NULL || a->header == NULL)
        return 1;

    return 0;
}

int
parse_article_header(struct article* a, struct sitemap* sm)
{
    char* html_header_fmt = "<!DOCTYPE html>\n"
        "<html lang=\"en\">\n"
        "<head>\n"
        "    <meta charset=\"UTF-8\">\n"
        "    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n"
        "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
        "    <title>%s - %s</title>\n"
        "</head>\n";

    a->html_header = xsnprintf(
                    strlen(html_header_fmt) + strlen(a->title) + strlen(sm->name) + 10,
                    html_header_fmt,
                    a->title, sm->name);

    return 0;
}

int
format_article(struct article* a, struct sitemap* sm)
{
    char* format = "%s<body>\n%s\n<article>\n"
        "<h2 class=\"article-title\">%s</h2>\n"
        "<p class=\"article-date\">%s</p>\n"
        "%s\n"
        "</article>\n"
        "</body>\n"
        "<style>\n"
        "%s\n"
        "%s\n"
        "%s\n"
        "</style>\n"
        "</html>\n";
    
    a->formatted = xsnprintf(
        strlen(a->html_header) + strlen(a->header) + strlen(a->html) +
            strlen(a->style) + strlen(sm->header_style) + strlen(sm->global_style) + 512,
        format,
        a->html_header, a->header, a->title, a->date, a->html, sm->global_style, sm->header_style, a->style
    );

    return 0;
}

int
parse_sitedir(char* src, char* dest, char** current_article_name, struct sitemap* sm)
{
    char* article_p = xsnprintf(256, "%s/articles", src);
    struct dirent* ent;
    DIR* dir = opendir(article_p);
    if (!dir)
        return 1;

    sm->articles = smalloc(sizeof(struct article));
    sm->article_count = 0;
    for (size_t i = 0; (ent = readdir(dir)) != NULL; i++) {
        char* dname = ent->d_name;
        if (!strcmp(dname, ".") || !strcmp(dname, ".."))
            continue;

        *current_article_name = xstrdup(dname);

        char* article_path = xsnprintf(256, "%s/articles/%s", src, dname);
        sm->articles = srealloc(sm->articles, sm->article_count + 1);

        struct article* a = scalloc(sizeof(struct article));
        sm->articles[sm->article_count] = a;
        init_article(a);

        if (parse_article(article_path, a, sm))
            return 1;
        if (parse_article_header(a, sm))
            return 1;
        
        format_article(a, sm);
        sm->article_count++;
        free(article_path);

        char* out_dir = xsnprintf(256, "%s/articles/%s.html", dest, dname);
        if (write_file(out_dir, a->formatted))
            return 1;

        free(out_dir);
        printf("parsed article: \"%s\" into file %s/articles/%s.html.\n", a->title, dest, dname);
    }
    closedir(dir);
    free(article_p);

    return 1;
}