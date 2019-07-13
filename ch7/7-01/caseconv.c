#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int c;
    if (strcmp(argv[0], "upper") == 0)
    {
        while ((c = getchar()) != EOF)
        {
            putchar(toupper(c));
        }
    }
    else if (strcmp(argv[0], "lower") == 0)
    {
        while ((c = getchar()) != EOF)
        {
            putchar(tolower(c));
        }
    }
    else
    {
        puts("must be invoked with program name 'upper' or 'lower'");
        return 1;
    }

    return 0;
}