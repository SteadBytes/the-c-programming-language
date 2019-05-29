#include <stdio.h>
#include <ctype.h>

double atof(char s[]);
int chtoi(char s);
int nonblankindex(char s[]);
int skipsign(char s[], int i);
int strsign(char s[], int i);
void display_result(char s[]);

int main(void)
{
    display_result("15");
    display_result("-15");
    display_result("123.45e-6");
    display_result("123.45E-6");
    display_result("123.45e6");
    display_result("123.45E6");
    return 0;
}

void display_result(char s[])
{
    printf("atof(%s) -> %f\n", s, atof(s));
}

/* chtoi: convert char s to int */
int chtoi(char s)
{
    return s - '0';
}

/* atof: convert string s to double */
double atof(char s[])
{
    int i = nonblankindex(s);
    int sign = strsign(s, i);
    i = skipsign(s, i);

    double val = 0.0;
    for (i; isdigit(s[i]); i++)
    {
        val = 10.0 * val + chtoi(s[i]);
    }

    if (s[i] == '.')
    {
        i++;
    }

    double power = 1.0;
    for (i; isdigit(s[i]); i++)
    {
        val = 10.0 * val + chtoi(s[i]);
        power *= 10.0;
    }
    val = sign * val / power;
    if (s[i] == 'e' || s[i] == 'E')
    {
        i++;
        sign = strsign(s, i);
        i = skipsign(s, i);
        int exp = 0;
        for (i; isdigit(s[i]); i++)
        {
            exp = 10 * exp + chtoi(s[i]);
        }
        exp *= sign;
        if (exp > 0)
        {
            while (exp-- > 0)
            {
                val = 10.0 * val;
            }
        }
        else
        {
            while (exp++ < 0)
            {
                val = val / 10.0;
            }
        }
    }
    return val;
}

/* strsign: return sign of substr at index i in s */
int strsign(char s[], int i)
{
    return (s[i] == '-') ? -1 : 1;
}

/* skipsign: return i incremented if s[i] is a +/i sign */
int skipsign(char s[], int i)
{
    return (s[i] == '+' || s[i] == '-') ? i++ : i;
}

/* nonblankindex: return index of first non-whitespace char */
int nonblankindex(char s[])
{
    int i;
    for (i = 0; isspace(s[i]); i++)
    { /* skip white space */
        ;
    }
    return i;
}