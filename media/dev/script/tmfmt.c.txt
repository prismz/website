/* program to format time - no license */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main(int argc, char** argv)
{
    if (argc < 2) {
        printf("0 seconds\n");
        return 0;
    }

    char* extra;
    int t = strtol(argv[1], &extra, 10);
    if (t <= 0) {
        printf("0 seconds\n");
        return 0;
    }

    int day = t / 60 / 60 / 24;
    int hour = t / 60 / 60 % 24;
    int min = t / 60 % 60;
    int sec = t % 60;

    if (day != 0) {
        printf("%d day", day);
        if (day > 1)
            printf("s");
    }
    if (hour != 0) {
        if (day != 0)
            printf(", ");

        printf("%d hour", hour);
        if (hour > 1)
            printf("s");
    }
    if (min != 0) {
        if (hour != 0 || day != 0)
            printf(", ");

        printf("%d minute", min);
        if (min > 1)
            printf("s");
    }
    if (sec != 0) {
        if (hour != 0 || day != 0 || min != 0)
            printf(", ");

        printf("%d second", sec);
        if (sec > 1)
            printf("s");
    }

    printf("\n");
}
