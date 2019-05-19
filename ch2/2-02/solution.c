#include <stdio.h>
#define MAXLINE 1000

int get_line(char line[], int maxline);

int main(void)
{
    int len;
    char line[MAXLINE]; /* current input line */
    while ((len = get_line(line, MAXLINE)) > 0)
    {
        printf("Your line was: %s\n", line);
    }
    return 0;
}

/* get_line: read a line into s, return length
    (underscore to prevent collision w/stdio)
    modified to not use && or || operators */
int get_line(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim - 1; ++i)
    {
        if ((c = getchar()) == EOF)
            break;

        s[i] = c;

        if (c == '\n')
            break;
    }
    s[i] = '\0';
    return i;
}