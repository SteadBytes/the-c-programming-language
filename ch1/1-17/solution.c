#include <stdio.h>
#define MAXLINE 1000 /* maximum input line length */
#define MINLINE 80   /* minimum input line length to print */

int get_line(char line[], int maxline);

/* print all input lines greater than 80 characters in length */
int main(void)
{
    int len;            /* current line length */
    char line[MAXLINE]; /* current input line */

    while ((len = get_line(line, MAXLINE)) > 0)
    {
        if (len > MINLINE)
        {
            puts(line);
        }
    }
    return 0;
}

/* get_line: read a line into s, return length
    (underscore to prevent collision w/stdio) */
int get_line(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
    {
        s[i] = c;
    }
    if (c == '\n')
    {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}