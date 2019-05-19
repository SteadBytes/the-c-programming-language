#include <stdio.h>
#define MAXLINE 1000 /* maximum input line length */

int get_line(char line[], int maxline);
void strip_right(char line[]);

/* remove trailing blanks and tabs from each line of input,
    and delete entirely blank lines */
int main(void)
{
    int len;                  /* current line length */
    char line[MAXLINE];       /* current input line */

    while ((len = get_line(line, MAXLINE)) > 0)
    {
        strip_right(line);
        int contains_chars = (line[0] != '\n' && line[0] != '\0');
        if (contains_chars)
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

/* strip_right: remove trailing blanks and tabs from a string */
void strip_right(char s[])
{
    int end_pos = -1;
    char c;
    int i;
    for (i = 0; (c = s[i]) != '\n' && c != '\0'; i++)
    {
        if (c == ' ' || c == '\t')
        {
            if (end_pos == -1)
            {
                end_pos = i;
            }
        }
        else
        {
            end_pos = -1;
        }
    }
    int strip_needed = (end_pos != -1 && i > 0);
    if (strip_needed)
    {
        /* include newline if present at end of original string */
        if (s[i] == '\n')
        {
            s[end_pos] = '\n';
            ++end_pos;
        }
        /* terminate string after final non-blank/tab char j*/
        s[end_pos] = '\0';
    }
}