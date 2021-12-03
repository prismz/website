#ifndef MD_H
#define MD_H

#include <wchar.h>

typedef enum {
	md_t_text,
	md_t_code,
	md_t_list,
	md_t_newline,
	md_t_eof
} md_token_t;

struct md_token {
	wchar_t* contents;
	struct md_token* next;
	struct md_token* prev;
	md_token_t type;
};

#endif
