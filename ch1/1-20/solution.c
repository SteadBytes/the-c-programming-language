#include <stdio.h>

#define MAXLINE 1000 /* maximum input line length */
#define TAB_WIDTH 4

int get_line(char line[], int maxline);
void detab(char src[], char result[], int tab_width);

/* replace all tabs in inputs with 4 spaces */
int main(void)
{
    int len;                               /* current line length */
    char src_line[MAXLINE];                /* current input line */
    char result_line[MAXLINE * TAB_WIDTH]; /* detabbed input line */

    while ((len = get_line(src_line, MAXLINE)) > 0)
    {
        detab(src_line, result_line, TAB_WIDTH);
        puts(result_line);
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

/* detab: copy src to result with tabs replaced by tab_width spaces */
void detab(char src[], char result[], int tab_width)
{
    char c;
    int j = 0;
    for (int i = 0; (c = src[i]) != '\0'; ++i)
    {
        if (c == '\t')
        {
            int spaces_end_pos = j + tab_width;
            for (j; j < spaces_end_pos; ++j)
            {
                result[j] = ' ';
            }
        }
        else
        {
            result[j] = c;
            ++j;
        }
    }
    result[j] = '\0';
}