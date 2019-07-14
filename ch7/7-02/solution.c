#include <stdio.h>
#include <ctype.h>

#define MAXLEN 100
#define CTRLLEN 5

/*
    print arbitrary input in a sensible way. Non-graphic characters are printed
    in hexadecimal according to local custom and long text lines are broken up.
*/
int advance_position(int, int);
int main(void)
{
    int c;
    int line_pos = 0;
    while ((c = getchar()) != EOF)
    {
        if (!isgraph(c))
        {
            line_pos = advance_position(line_pos, CTRLLEN);
            printf(" \\%02x ", c); // CTRLLEN width
            if (c == '\n')
            {
                line_pos = 0;
                putchar('\n');
            }
        }
        else
        {
            line_pos = advance_position(line_pos, 1);
            putchar(c);
        }
    }
    return 0;
}

int advance_position(int line_pos, int width)
{
    if (line_pos + width < MAXLEN)
    {
        return line_pos + width;
    }
    else
    {
        putchar('\n');
        return width;
    }
}