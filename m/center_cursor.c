#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

void
die(char* fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    vfprintf(stderr, fmt, vl);
    va_end(vl);
    exit(EXIT_FAILURE);
}

void*
smalloc(size_t size)
{
    void* mem = malloc(size);
    if (mem == NULL)
        die("center_cursor: fatal: malloc() failed.\n");

    return mem;
}

int
main(void)
{
    FILE* fp = popen("xrandr", "r");
    if (!fp)
        die("center_cursor: fatal: failed to get output of xrandr.\n");

    char* buf = smalloc(sizeof(char) * 2048);
    while (fgets(buf, 2048, fp) != NULL) {
        if (strstr(buf, "primary") != NULL) {
            break;
        }
    }

    char* b;  /* for strtol */

    buf[strlen(buf) - 1] = '\0';
    char* dims = strtok(buf, " ");
    for (int i = 0; i < 3; i++)
        dims = strtok(NULL, " ");

    /* evil variable name */
    char* _sdims = strtok(dims, "+");
    char* sdims = strdup(_sdims);
    if (sdims == NULL)
        die("center_cursor: fatal: strdup() failed.\n");
    _sdims = strtok(NULL, "+");
    char* offset = _sdims;

    char* c_ow = strtok(offset, "+");
    int ow = strtol(c_ow, &b, 10);
     
    char* sh = strtok(sdims, "x");
    char* sw = sh;
    sh = strtok(NULL, "x");

    int nx = strtol(sw, &b, 10) / 2 + ow;
    int ny = strtol(sh, &b, 10) / 2;

    char* cmd = smalloc(sizeof(char) * 1024);
    snprintf(cmd, 1024, "xdotool mousemove %d %d && xdotool click 1", nx, ny);
    system(cmd);

    free(cmd);
    free(sdims);
    free(buf);

    pclose(fp);
}
