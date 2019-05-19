#include <stdio.h>

#define MAXLINE 1000

int htoi(char s[]);
int hchartoi(char c);
int get_line(char line[], int maxline);

int main(void)
{
    puts("Enter a hexidecimal string to convert to an integer (optional \\x or \\X prefix)");
    char line[MAXLINE];
    int len;
    while ((len = get_line(line, MAXLINE)) > 0)
    {
        if (line[len - 1] == '\n')
            line[len - 1] = '\0';
        int v = htoi(line);
        if (v == -1)
        {
            printf("Invalid hexidecimal string: %s", line);
            return 1;
        }
        printf("%d\n", htoi(line));
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

/* htoi: convert a string of hexadecimal digits (0x 0X prefix optional) into its
    equivalent integer value. Allowable digits: [0-9a-fA-F]*/
int htoi(char s[])
{
    int is_prefixed = s[0] == '0' && (s[1] == 'x' || s[1] == 'X');
    int i = 0;
    if (is_prefixed)
        i = 2;
    char c;
    int result = 0;
    for (i; (c = s[i]) != '\0'; ++i)
    {
        int char_val = hchartoi(c);
        // invalid hex character
        if (char_val == -1)
            return -1;
        result = result * 16 + char_val;
    }
    return result;
}

/* htoi: convert a char representing a hexidecimal digit into its equivalent
    integer value. Allowable digits: [0-9a-fA-F] */
int hchartoi(char c)
{
    if (c >= '0' && c <= '9')
        return (c - '0');
    else if (c >= 'a' && c <= 'f')
        return 10 + c - 'a';
    else if (c >= 'A' && c <= 'F')
        return 10 + c - 'A';
    else
        // invalid hex character
        return -1;
}