#ifndef CSG_ARTICLE_H
#define CSG_ARTICLE_H

#include <stdlib.h>

#define FREE_IF_NULL(x) if (x != NULL) free(x);

struct sitemap;
struct article;

struct sitemap {
    char* name;

    char* header_path;
    char* index_path;
    char* style_path;
    char* global_style_path;
    char* header_style_path;
    char* article_style_path;

    char* header;
    char* index;
    char* style;
    char* global_style;
    char* header_style;
    char* article_style;

    struct article** articles;
    size_t article_count;
};

struct article {
    char* title;
    char* date;

    char* header_path;
    char* html_path;
    char* style_path;

    char* html_header;
    char* header;
    char* html;
    char* style;

    char* formatted;
};

void init_sitemap(struct sitemap* sm);
void init_article(struct article* a);
void free_sitemap(struct sitemap* sm);
void free_article(struct article* a);

int populate_sitemap(char* srcdir, struct sitemap* sm);
int parse_article_metadata(char* article_dir, struct article* a);
int parse_article(char* article_dir, struct article* a, struct sitemap* sm);
int parse_article_header(struct article* a, struct sitemap* sm);
int format_article(struct article* a, struct sitemap* sm);
int parse_sitedir(char* src, char* dest, char** current_article_name, struct sitemap* sm);

#endif