#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "calc.h"

int getop(char s[])
{
    int i, c, c2;
    /* 
        ex 4-11: use internal static variable to track previous characer
        -> removes need for ungetch
    */
    static int prevc = 0;

    /* check for pushed back character */
    if (prevc)
    {
        c = prevc;
        prevc = 0;
    }
    else
    {
        c = getch();
    }

    while ((s[0] = c) == ' ' || c == '\t')
    {
        c = getch();
    }
    s[1] = '\0';
    i = 0;
    if (islower(c)) /* ex 4-05: command or FUNCTION */
    {
        while (islower(s[++i] = c = getch()))
        {
            ;
        }
        s[i] = '\0';
        if (c != EOF)
        {
            prevc = c;
        }
        if (strlen(s) > 1)
        {
            return FUNCTION; /* FUNCTION i.e. sin, cos, pow etc */
        }
        else
        {
            /* command i.e. d to duplicate top stack item or  ex 4-06 variable */
            return isalpha(c) ? c : s[i - 1];
        }
    }
    if (!isdigit(c) && c != '.' && c != '-')
    {
        return c; /* not a number */
    }

    if (c == '-') /*ex 4-03 */
    {
        c2 = getch();
        if (c2 != EOF)
        {
            prevc = c2;
        }
        if (!isdigit(c2) && c2 != '.')
        {
            return c;
        }
    }
    if (isdigit(c) || c == '-') /* ex 4-03 */
    {                           /* collect integer part */
        while (isdigit(s[++i] = c = getch()))
        {
            ;
        }
    }
    if (c == '.')
    { /* collect fraction part */
        while (isdigit(s[++i] = c = getch()))
        {
            ;
        }
    }
    s[i] = '\0';
    if (c != EOF)
    {
        prevc = c;
    }
    return NUMBER;
}