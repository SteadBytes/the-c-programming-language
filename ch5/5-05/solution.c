#include <stdio.h>

#define MAXLINE 1000

void strn_cpy(char *s, char *t, int n);
void strn_cat(char *s, char *t, int n);
int strn_cmp(char *s, char *t, int n);

int main(void)
{
    char s[MAXLINE];
    char t[MAXLINE] = "this is a sentence";
    int n = 3;
    printf("strn_cpy(\"%s\", \"%s\", %d) -> ", s, t, n);
    strn_cpy(s, t, n);
    puts(s);

    strn_cpy(s, "hello world", 20);
    printf("strn_cat(\"%s\", \"%s\", %d) -> ", s, t, n);
    strn_cat(s, t, n);
    puts(s);

    strn_cpy(s, "hello world", 20);
    strn_cpy(t, "hello person", 20);
    printf("strn_cmp(\"%s\", \"%s\", %d) -> %d\n", s, t, n, strn_cmp(s, t, n));
    n = 7;
    printf("strn_cmp(\"%s\", \"%s\", %d) -> %d\n", s, t, n, strn_cmp(s, t, n));
    return 0;
}

/*
    strn_cpy: copy at most n characters of t to s
    s size must be >= strlen(s) + n
*/
void strn_cpy(char *s, char *t, int n)
{
    while (n-- > 0 && (*s++ = *t++))
    {
    }

    /* ensure s is terminated if strlen(t) < n */
    while (n-- > 0)
    {
        *s++ = '\0';
    }
}

/*
    str_cat: copy at most n characters from string t to the end of s 
    s size must be >= strlen(s) + n in order to contain the concatenation
*/
void strn_cat(char *s, char *t, int n)
{
    while (*s)
    {
        s++;
    }
    while (n-- > 0 && (*s++ = *t++))
    {
    }
}

/*
    strn_cmp: compare at most the first n chars of s and t
    return < 0 if s[:n] < t[:n]
    return > 0 if t[:n] > s[:n]
    return 0 if s[:n] == t[:n]
*/
int strn_cmp(char *s, char *t, int n)
{

    for (; *s == *t; s++, t++)
    {
        if (*s == '\0' || --n <= 0)
        {
            return 0;
        }
    }
    return *s - *t;
}