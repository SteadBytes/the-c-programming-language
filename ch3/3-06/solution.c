#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

void itoa(int n, char s[], int b);
void display_result(int n, char s[], int width);
void reverse(char s[]);
int abs(int x);

int main(void)
{
    char s[MAXLINE];
    display_result(10, s, 2);
    display_result(10, s, 5);
    display_result(-10, s, 2);
    display_result(1024, s, 15);
    return 0;
}

void display_result(int n, char s[], int width)
{
    itoa(n, s, width);
    printf("n=%d, width=%d -> %s\n", n, width, s);
}

/*
    itoa: convert n to characters in s, left padded with blanks to width chars
*/
void itoa(int n, char s[], int width)
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
    /* left pad with blanks up to width */
    while (width > i)
    {
        s[i++] = ' ';
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