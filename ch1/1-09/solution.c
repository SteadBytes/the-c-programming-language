#include <stdio.h>

main()
{
    int c, prev_blank;

    while ((c = getchar()) != EOF)
    {
        if (c == ' ')
        {
            if (!prev_blank)
            {
                prev_blank = 1;
                putchar(c);
            }
        }
        else
        {
            prev_blank = 0;
            putchar(c);
        }
    }
}