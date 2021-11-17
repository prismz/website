#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int
main(void)
{
    char* nonprintables[] = {
        "NULL",
        "HEADER START",
        "TEXT START",
        "TEXT END",
        "TRANSMISSION END",
        "ENQUIRY",
        "ACKNOWLEDGE",
        "BELL",
        "BACKSPACE",
        "HORIZONTAL TAB",
        "LINE FEED",
        "VERTICAL TAB",
        "FORM FEED",
        "CARRIAGE RETURN",
        "SHIFT OUT",
        "SHIFT IN",
        "DATA LINK ESC",
        "DEVCTL 1",
        "DEVCTL 2",
        "DEVCTL 3",
        "DEVCTL 4",
        "NEGATIVE ACKNOWLEDGE",
        "SYNCHRONOUS IDLE",
        "END TRANS BLOCK",
        "CANCEL",
        "END OF MEDIUM",
        "SUBSTITUTE",
        "ESCAPE",
        "FILE SEPARATOR",
        "GROUP SEPARATOR",
        "RECORD SEPARATOR",
        "UNIT SEPARATOR"
    };
    
    int i;
    for (i = 0; i < 32; i++) {
        printf("%03d: %s\n", i, nonprintables[i]);
    }

    for (i = i; i < 127; i++)
        printf("%03d: '%c'\n", i, i);

    printf("127: DEL\n");
}
