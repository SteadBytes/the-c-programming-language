#include <stdio.h>

#define MAXTOKEN 100 /* max size of any token */

enum
{
    NAME,
    PARENS,
    BRACKETS
};

extern int token_type;       /* type of last token */
extern char token[MAXTOKEN]; /* last token */
extern int token_available;

int get_token(void);
int peek_token(void);
void handle_parse_err(char *msg);
int is_brackets(int type);