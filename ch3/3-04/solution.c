#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAXLINE 1000

void itoa(int n, char s[]);
void reverse(char s[]);
int abs(int x);

int main(void)
{
    char s[MAXLINE];
    itoa(INT_MIN, s);
    printf("INT_MIN chars = %s\n", s);
    return 0;
}

/*
    itoa: convert n to characters in s
    original version doesn't work for largest negative number:
        largest negative number in two's complement = -(2^(wordsize-1))
        largest positive number in two's complement = 2^(wordsize-1)-1
        original version will convert a negative n to positive with n = -n;
            -(-(2^(wordsize-1))) = 2^(wordsize-1) -> TOO BIG
*/
void itoa(int n, char s[])
{
    int is_negative = n < 0;
    int i = 0;
    do
    {
        /*
            convert each digit to positive instead of whole n
            will always be less than largest possible positive number
        */
        s[i++] = abs(n % 10) + '0';
    } while ((n /= 10) != 0); /* n may be negative -> stop when no more digits */
    if (is_negative)
    {
        s[i++] = '-';
    }
    s[i] = '\0';
    reverse(s);
}

/* reverse: reverse string s in place (from ch3.5) */
void reverse(char s[])
{
    for (int i = 0, j = strlen(s) - 1; i < j; i++, j--)
    {
        char c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

/* abs: return absolute value of x */
int abs(int x)
{
    return (x < 0) ? -x : x;
}