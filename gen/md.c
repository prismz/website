#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main(void)
{
	char* c = malloc(sizeof(char) * 4096);
	while (fgets(c, 4096, stdin) != NULL) {
		c[strlen(c) - 1] = '\0';

		if (c[0] == '#') {  /* parse a header */
			int i;
			for (i = 0; i < (int)strlen(c); i++) {
				if (c[i] != '#')
					break;
			}

			for (; (c + i)[0] == ' '; i++);  /* strip leading whitespace */

			printf("<h%d>%s</h%d>\n", i, c + i, i);
		} else if (!strcmp(c, "")) { 
			printf("<br><br>\n");
		} else {
			printf("%s\n", c);
		}
	}

	free(c);
}
