#include <stdio.h>
#include <ctype.h>

#define SIZE 100

int getch(void);
void ungetch(int);
float append_digit(float x, char c);

int main(void)
{
    float array[SIZE];
    int getfloat(float *pn);
    int n;
    for (n = 0; n < SIZE && getfloat(&array[n]) != EOF; n++)
    {
        ;
    }
    puts("floats read from input:");
    for (int i = 0; i < n; i++)
    {
        printf("%f\n", array[i]);
    }

    return 0;
}

/*
    getfloat: get next float from input into *pn 
    returns first char after the float in input or EOF
*/
int getfloat(float *pn)
{
    int c;
    while (isspace(c = getch()))
    { /* skip white space */
    }

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
    for (*pn = 0.0; isdigit(c); c = getch())
    {
        *pn = append_digit(*pn, c); /* add digits from integer portion */
    }
    if (c == '.')
    {
        c = getch(); /* skip over decimal point */
    }
    float power;
    for (power = 1.0; isdigit(c); c = getch())
    {
        *pn = append_digit(*pn, c); /* add digits from fractional portion */
        power *= 10.0;           /* track 'column' reached i.e. 10^-1, 10^-2 ... */
    }
    *pn *= sign / power; /* calculate final value */
    if (c != EOF)
    {
        ungetch(c);
    }
    return c;
}

/* append_digit: add digit represented by c to next 'column' in x */
float append_digit(float x, char c)
{
    return 10.0 * x + (c - '0');
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