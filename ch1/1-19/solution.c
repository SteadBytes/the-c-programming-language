#include <stdio.h>
#define MAXLINE 1000 /* maximum input line length */

int get_line(char line[], int maxline);
void swap(char s[], int i, int j);

/* reverse input one line at a time */
int main(void)
{
    int len;            /* current line length */
    char line[MAXLINE]; /* current input line */

    while ((len = get_line(line, MAXLINE)) > 0)
    {
        /* keep trailing \n if present in input line */
        if (line[len - 1] == '\n')
        {
            --len;
        }

        char tmp;
        for (int i = 0; i < len / 2; ++i)
        {
            int j = len - 1 - i;
            swap(line, i, j);
        }
        puts(line);
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

/* swap: swap characters at positions i, j in string s*/
void swap(char s[], int i, int j)
{
    char tmp = s[i];
    s[i] = s[j];
    s[j] = tmp;
}