#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERSION "1.0"
#define PNAME "perms2num"

static int verbose = 0;

void
usage(void)
{
    printf("%s v%s: convert permissions to a number for use with chmod.\n", PNAME, VERSION);
    printf("ex: %s rwxr-xr-x -> 755\n", PNAME);
    printf("invalid strings will return 000.\n");
    printf("    -V --version      print the version and info and exit.\n");
    printf("    -v --verbose      print the corresponding line or permission string for each number.\n");
    printf("author: Hasan Zahra - github.com/prismz\n");
    printf("licensed under GPLv3 or later.\n");
    exit(0);
}

int
chars2num(char* str)
{
    int n = 0;
    for (int i = 0; i < 3; i++) {
        switch (str[i]) {
        case 'r':
            n += 4;
            break;
        case 'w':
            n += 2;
            break;
        case 'x':
            n += 1;
            break;
        }
    }

    return n;
}

void
str2num(char* str, char* dat)
{
    int i;
    char c1[4], c2[4], c3[4];
    for (i = 0; i < 3; i++)
        c1[i] = str[i];
    c1[i] = '\0';

    for (i = 3; i < 6; i++)
        c2[i - 3] = str[i];
    c2[i - 3] = '\0';

    for (i = 6; i < 10; i++)
        c3[i - 6] = str[i];
    c3[i - 6] = '\0';

    int n1, n2, n3;
    n1 = chars2num(c1);
    n2 = chars2num(c2);
    n3 = chars2num(c3);

    printf("%d%d%d", n1, n2, n3);
    if (verbose)
        printf(": %s", dat);
    printf("\n");
}

int
main(int argc, char** argv)
{
    verbose = 1;
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "--version") || !strcmp(argv[i], "-V"))
            usage();
        if (!strcmp(argv[i], "--verbose") || !strcmp(argv[i], "-v")) {
            verbose = 1;
            continue;
        }
    }
    if (argc == 2)
        verbose = 0;

    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (strlen(argv[i]) == 10)
                argv[i]++;
            if (strlen(argv[i]) == 9)
                str2num(argv[i], argv[i]);
        }

        return 0;
    }
   
    verbose = 1;

    char c;
    size_t allocated = 1024, i = 0;
    char* buffer = malloc(sizeof(char) * allocated);
    while ((c = fgetc(stdin)) != EOF) {
        if (i + 1 > allocated)
            buffer = realloc(buffer, allocated += 512);
        buffer[i++] = c;
    }
    buffer[i] = '\0';

    char cb[10];
    char* ptr = strtok(buffer, "\n");
    while (ptr != NULL) {
        if (strlen(ptr) >= 9) {
            int j;
            for (j = 1; j < 10; j++)
                cb[j-1] = ptr[j];
            cb[j] = '\0';
            str2num(cb, ptr);
        }
        ptr = strtok(NULL, "\n");
    }

    free(buffer);
}
