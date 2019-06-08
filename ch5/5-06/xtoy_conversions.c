#include <stdio.h>
#include <string.h>
#include <ctype.h>

int atoi(char *s);
void itoa(int n, char *s);
double atof(char *s);
void reverse(char *s);
int abs(int x);

int main(void)
{
    char s[] = "this is a sentence";
    printf("reverse(%s) -> ", s);
    reverse(s);
    puts(s);

    char s2[] = "12345";
    printf("atoi(\"%s\") -> %d\n", s2, atoi(s2));

    int n = 1234;
    itoa(n, s);
    printf("itoa: %d -> %s\n", n, s);

    char s3[] = "123.456";
    printf("atof(\"%s\") -> %f\n", s3, atof(s3));

    return 0;
}

/* atoi: convert s to integer */
int atoi(char *s)
{
    while (isspace(*s))
    {
        /* skip white space */
        s++;
    }
    int sign = (*s == '-') ? -1 : 1;
    if (*s == '+' || *s == '-')
    {
        s++; /* skip sign */
    }
    int n;
    for (n = 0; isdigit(*s); s++)
    {
        n = 10 * n + (*s - '0');
    }
    return sign * n;
}

/* itoa:  convert n to characters in s */
void itoa(int n, char *s)
{
    char *start = s;
    int is_negative = n < 0;
    do
    {
        /*
            convert each digit to positive instead of whole n
            will always be less than largest possible positive number
        */
        *s++ = abs(n % 10) + '0';
    } while ((n /= 10) != 0); /* n may be negative -> stop when no more digits */
    if (is_negative)
    {
        *s++ = '-';
    }
    *s = '\0';
    reverse(start);
}

/* atof: convert string s to double */
double atof(char *s)
{
    while(isspace(*s)) {
        /* skip white space */
        s++;
    }
    int sign = (*s == '-') ? -1 : 1;
    if (*s == '+' || *s == '-')
    {
        s++; /* skip sign */
    }

    double val;
    for (val=0.0; isdigit(*s); s++)
    {
        val = 10.0 * val + (*s - '0');
    }
    if (*s == '.')
    {
        s++; /* skip decimal point */
    }
    double power;
    for (power = 1.0; isdigit(*s); s++)
    {
        val = 10.0 * val + (*s - '0');
        power *= 10.0;
    }
    return sign * val / power;
}

void reverse(char *s)
{
    char *end = s + strlen(s);
    for (char *end = s + (strlen(s) - 1); s < end; s++, end--)
    {
        char c = *s;
        *s = *end;
        *end = c;
    }
}

/* abs: return absolute value of x */
int abs(int x)
{
    return (x < 0) ? -x : x;
}
