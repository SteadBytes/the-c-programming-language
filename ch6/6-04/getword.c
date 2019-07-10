#include "getword.h"

/*
    getword: get next word or character from input.
    Returns first character of word, EOF if end of input reached or
    single char if not alphabetic
*/
int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    /* don't skip newlines -> allow caller to track number of lines */
    while (isspace(c = getch()) && c != '\n')
    {
        ;
    }
    if (c != EOF)
    {
        *w++ = c;
    }
    /* treat non alphabetic chars as individual tokens */
    if (!isalpha(c))
    {
        *w = '\0';
        return c;
    }
    /* collect string of alphanumeric chars */
    for (; --lim > 0; w++)
    {
        if (!isalnum(*w = getch()))
        {
            /* one char too far (not alphanumeric) -> push back */
            ungetch(*w);
            break;
        }
    }
    *w = '\0';
    return word[0];
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