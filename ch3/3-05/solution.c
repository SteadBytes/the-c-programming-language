#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

void itob(int n, char s[], int b);
void reverse(char s[]);
int abs(int x);

int main(void)
{
    char s[MAXLINE];
    const int n_count = 8;
    const int b_count = 4;
    int n_arr[] = {2, 4, 5, 16, 25, 256, 1023, -1023};
    int b_arr[] = {2, 8, 10, 16};
    for (int i = 0; i < n_count; i++)
    {
        int n = n_arr[i];
        for (int j = 0; j < b_count; j++)
        {
            int b = b_arr[j];
            itob(n, s, b);
            printf("%d -> base %d = %s\n", n, b, s);
        }
    }
    return 0;
}

/*
    itob: convert n into a base b character representation in s
*/
void itob(int n, char s[], int b)
{
    int is_negative = n < 0;
    int i = 0;
    do
    {
        int r = abs(n % b);
        s[i++] = (r < 10) ? r + '0' : r - 10 + 'a';
    } while ((n /= b) != 0);
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