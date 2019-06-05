#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAXLINE 1000

void itoa(int n, char s[]);
int abs(int x);

int main(void)
{
    char s[MAXLINE];
    itoa(INT_MAX, s);
    printf("INT_MAX as chars = %s\n", s);
    itoa(INT_MIN, s);
    printf("INT_MIN as chars = %s\n", s);
    return 0;
}

/* itoa: ex 4-12: convert n to characters in s via a recursive procedure */
void itoa(int n, char s[])
{
    /* index for s, static -> same variable each recursive call */
    static int i;

    int remaining_digits = n / 10;
    if (remaining_digits)
    {
        /* recursive case: more than 1 digit present in n */
        itoa(remaining_digits, s);
    }
    else
    {
        /*
            base case: single digit
        */
        i = 0;
        /* check for negative, begin string with '-' if necessary */
        if (n < 0)
        {
            s[i++] = '-';
        }
    }
    s[i++] = abs(n % 10) + '0';
    /* NUL overwritten by next recursive call if needed */
    s[i] = '\0';
}

/* abs: return absolute value of x */
int abs(int x)
{
    return (x < 0) ? -x : x;
}