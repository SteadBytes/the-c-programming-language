#include <stdio.h>

#define MAXLINE 1000

int strend(char *s, char *t);

int main(void)
{
    char s[MAXLINE] = "hello, ";
    char t[MAXLINE] = "world!";
    printf("strend(%s, %s) -> %d", s, t, strend(s, t));
    puts(s);
    return 0;
}

/*
    strend: return 1 if string t occurs at the end of string s else zero
*/
int strend(char *s, char *t)
{
    /* save start positions of both strings */
    char *s_start = s;
    char *t_start = t;

    /* find end position of both strings */
    while (*s)
    {
        s++;
    }
    while (*t)
    {
        s++;
    }

    /* traverse backwards whilst characters are equal */
    for (; *s == *t; s--, t--)
    {
        /* beginning of string reached */
        if (s == s_start || t == t_start)
        {
            break;
        }
    }
    /* final reached characters the same, entire of t traversed and not \0 */
    return (*s == *t && t == t_start && *s != '\0') ? 1 : 0;
}