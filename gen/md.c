#include "util.h"
#include "md.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <wchar.h>
#include <locale.h>

int
parse(wchar_t* str)
{
    size_t added = 0;
    wchar_t* buffer = safe_malloc(sizeof(wchar_t) * (wcslen(str) * 2));

	wchar_t c, pc;
	for (size_t i = 1; i < wcslen(str); i++) {
		c = str[i];	
		pc = str[i - 1];
	}

    return 0;
}

int
main(void)
{
    setlocale(LC_ALL, "en_US.UTF-8");

    wchar_t* r = read_file("../md/software/linuxgaming.md");
    parse(r);
    free(r);
}
