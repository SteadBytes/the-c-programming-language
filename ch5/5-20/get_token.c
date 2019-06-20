#include <string.h>
#include <ctype.h>

#include "get_token.h"

int token_type;       /* type of last token */
char token[MAXTOKEN]; /* last token */
int token_available = 0;

/* get_token: return next token in input */
int get_token(void)
{
    /* do not retrieve a new token if one is already available */
    if (token_available)
    {
        token_available = 0;
        return token_type;
    }

    int getch(void);
    void ungetch(int);

    int c;
    char *p = token;
    while ((c = getch()) == ' ' || c == '\t') /* skip blanks */
    {
        ;
    }

    if (c == '(')
    {
        if ((c = getch()) == ')')
        {
            strcpy(token, "()");
            return token_type = PARENS;
        }
        else
        {
            ungetch(c);
            return token_type = '(';
        }
    }
    else if (c == '[')
    {
        for (*p++ = c; (*p++ = getch()) != ']';)
        {
            ;
        }
        *p = '\0';
        return token_type = BRACKETS;
    }
    else if (isalpha(c))
    {
        for (*p++ = c; isalnum(c = getch());)
        {
            *p++ = c;
        }
        *p = '\0';
        ungetch(c);
        return token_type = NAME;
    }
    else
    {
        return token_type = c;
    }
}

/* peek_token: get next token in input then push back (ex 5-19)*/
int peek_token(void)
{
    int type = get_token();
    token_available = 1;
    return type;
}

#define BUFSIZE 100

char buf[BUFSIZE]; /* ungetch buffer */
int bufp = 0;      /* next free position in buf */

/* getch: get a (possibly pushed back) character */
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* ungetch: push character back on input */
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
    {
        puts("ungetch: too many characters");
    }
    else
    {
        buf[bufp++] = c;
    }
}

/*
    handle_parse_err: print error message and indicate that a token is available
    due to error parsing a part of a declaration
*/
void handle_parse_err(char *msg)
{
    puts(msg);
    token_available = 1;
}

/* is_brackets: return 1 if type is () or [] else 0 */
int is_brackets(int type)
{
    return type == PARENS || type == BRACKETS;
}