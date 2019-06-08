#include <stdio.h>

#define MAXLINE 1000

int get_line(char *s, int lim);

int main(void)
{
    char s[MAXLINE];
    printf("Enter a line to test get_line: ");
    printf("Characters entered: %d\n", get_line(s, MAXLINE));
    printf("Line: %s\n", s);
    return 0;
}

/* get_line: read a line into s, return length
    (underscore to prevent collision w/stdio) */
int get_line(char *s, int lim)
{
    /* save start address to calculate length */
    char *start = s;
    /* read chars into s from stdin */
    int c;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
    {
        *s++ = c;
    }
    /* include newline if present */
    if (c == '\n')
    {
        *s++ = c;
    }
    *s = '\0';
    return s - start;
}