#include <stdio.h>
#include <ctype.h>

#define SIZE 100

int getch(void);
void ungetch(int);

int main(void)
{
    int array[SIZE], getint(int *);
    for (int n = 0; n < SIZE && getint(&array[n]) != EOF; n++)
    {
        ;
    }
    return 0;
}

/* getint: get next integer from input into *pn */
int getint(int *pn)
{
    int c;

    while (isspace(c = getch())) /* skip white space */
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-')
    {
        ungetch(c); /* not a number */
        return 0;
    }
    int sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
    {
        int sign_char = c;
        /* + or - not followed by digit are pushed back on to input */
        if (!isdigit(c = getch()))
        {
            if (c != EOF)
            {
                /* non-digit -> push back */
                ungetch(c);
            }
            ungetch(sign_char);
            return sign_char;
        }
    }
    for (*pn = 0; isdigit(c); c = getch())
    {
        *pn = 10 * *pn + (c - '0');
    }
    *pn *= sign;
    if (c != EOF)
    {
        ungetch(c);
    }
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