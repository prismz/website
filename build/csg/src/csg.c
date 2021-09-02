#include "csg.h"
#include "mem.h"
#include "util.h"
#include "str.h"
#include "article.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>

int
main(int argc, char** argv)
{
    if (argc < 3)
        die("please provide args\n");

    char* src = argv[1];
    char* dest = argv[2];

    struct sitemap sm;
    init_sitemap(&sm);
    populate_sitemap(src, &sm);

    char* article_name;
    if (!parse_sitedir(src, dest, &article_name, &sm))
        die("error parsing article %s.\n", article_name);

    free_sitemap(&sm);

}