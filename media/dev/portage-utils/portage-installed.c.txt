#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>

int
main(void)
{
    size_t c = 0;
    struct dirent* ent;
    DIR* dir = opendir("/var/db/pkg");
    if (!dir)
        return 1;

    while ((ent = readdir(dir)) != NULL) {
        if (!strcmp(ent->d_name, ".") || !strcmp(ent->d_name, ".."))
            continue;

        char* p = malloc(strlen(ent->d_name) + 50);
        snprintf(p, strlen(ent->d_name) + 50, "/var/db/pkg/%s", ent->d_name);

        struct dirent* e2;
        DIR* d2 = opendir(p);
        if (!d2)
            return 1;

        while ((e2 = readdir(d2)) != NULL) {
            if (!strcmp(e2->d_name, ".") || !strcmp(e2->d_name, ".."))
                continue;
            
            printf("%s/%s\n", ent->d_name, e2->d_name);
            c++;
        }

        closedir(d2);
        free(p);
    }

    closedir(dir);

    printf("total: %zu\n", c);
    return 0;
}
