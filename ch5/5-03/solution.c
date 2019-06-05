#include <stdio.h>

#define MAXLINE 1000

void str_cat(char *s, char *t);

int main(void)
{
    char s[MAXLINE] = "hello, ";
    char t[MAXLINE] = "world!";
    printf("strcat(%s, %s) -> ", s, t);
    str_cat(s, t);
    puts(s);
    return 0;
}

/*
    str_cat: copy string t to the end of s (renamed to avoid built-in conflict
    s size must be >= strlen(s) + strlen(t) in order to contain the
    concatenation of s and t
*/
void str_cat(char *s, char *t)
{
    while (*s)
    {
        s++;
    }
    while (*s++ = *t++)
    {
    }
}