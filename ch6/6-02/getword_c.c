#include "getword_c.h"

/*
    getword_c: get next word or character from input treated as C source code
    returns value of first character of word, EOF or character if not alphabetic
    comments are ignored, string literals include quotation marks, preprocessor
    commands and _ separated tokens are returned as single words
*/
int getword_c(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))
    {
        ;
    }
    if (c != EOF)
    {
        *w++ = c;
    }
    /* tokens, preprocessor commands and '_' separated tokens */
    if (isalpha(c) || c == '#' || c == '_')
    {
        for (; --lim > 0; w++)
        {
            if (!isalnum(*w = getch()) && *w != '_') /* handle '_' separator */
            {
                ungetch(*w);
                break;
            }
        }
    }
    /* string literal */
    else if (c == '"' || c == '\'')
    {
        for (; --lim > 0; w++)
        {
            /* escaped character */
            if ((*w = getch()) == '\\')
            {
                *++w = getch();
            }
            /* enclosing quote found */
            else if (*w == c)
            {
                w++;
                break;
            }
            else if (*w == EOF)
            {
                break;
            }
        }
    }
    /* handle comments */
    else if (c == '/')
    {
        int c2 = getch();
        if (c2 == '*') /* start of comment */
        {
            while ((c = getch()) != EOF)
            {
                if (c == '*')
                {
                    if ((c = getch()) == '/') /* end of comment */
                    {
                        *w-- = '\0'; /* remove starting '/' -> return empty */
                        break;
                    }
                    else /* '*' present mid comment */
                    {
                        ungetch(c);
                    }
                }
            }
        }
        else /* not a comment */
        {
            ungetch(c2);
        }
    }

    *w = '\0';
    return c;
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