#include <stdio.h>

#define BUFSIZE 100

/*
    ex 4-09: handle pushed back EOF
    buf was previously a char array. When EOF (int -1) is converted to a char
    the resulting value may be different between C implementations. Some may
    produce 255, others may produce -1. Changing buf to an int array will
    overcome this as no conversion is necessary.
 */
int buf[BUFSIZE]; /* ungetch buffer */
int bufp = 0;     /* next free position in buf */

/* getch: get a (possibly pushed back) character */
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}