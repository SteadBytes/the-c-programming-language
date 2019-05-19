#include <stdio.h>

#define MAXLINE 1000 /* maximum input line length */
#define TAB_WIDTH 4

int get_line(char line[], int maxline);
void entab(char src[], char result[], int tab_width);
int substr_blank(char s[], int i, int j);

/* replace strings of blanks in input by minimum number
    of tabs and blanks to achieve the same spacing */
int main(void)
{
    int len;                               /* current line length */
    char src_line[MAXLINE];                /* current input line */
    char result_line[MAXLINE * TAB_WIDTH]; /* entabbed input line */

    while ((len = get_line(src_line, MAXLINE)) > 0)
    {
        entab(src_line, result_line, TAB_WIDTH);
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

/* entab: copy src to result with strings of blanks replaced by the minimum
    number of tabs and spaces to achieve the same spacing */
void entab(char src[], char result[], int tab_width)
{
    char c;
    int j = 0;
    for (int i = 0; (c = src[i]) != '\0'; ++i)
    {
        if (c == ' ' && substr_blank(src, i, i + tab_width))
        {
            result[j] = '\t';
            ++j;
            i += tab_width - 1;
        }
        else
        {
            result[j] = c;
            ++j;
        }
    }
    result[j] = '\0';
}

/* substr_blank return 1 if the substring from index i to j (exclusive) of
    s is blank */
int substr_blank(char s[], int i, int j)
{
    for (i; i < j; i++)
    {
        if (s[i] != ' ')
        {
            return 0;
        }
    }
    return 1;
}