#include <stdio.h>

int lower(char c);

int main(void)
{
    char c;
    while ((c = getchar()) != EOF)
    {
        putchar(lower(c));
    }

    return 0;
}

/* lower: convert char to lowercase */
int lower(char c)
{
    return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}