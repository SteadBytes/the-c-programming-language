#include <stdio.h>
#include <ctype.h>

#define MAXLINE 1000

void expand(char s1[], char s2[]);

int main(void)
{
    char s1[MAXLINE] = "a-c A-D 0-2 a-c0-2 -ab az-";
    char s2[MAXLINE];
    puts(s1);
    expand(s1, s2);
    puts(s2);
    return 0;
}

/*
    expand: copy s1 to s2, converting shorthand notations like a-z into the 
    complete list abc..xyz i.e. a-c -> abc, 0-2 -> 012    
*/
void expand(char s1[], char s2[])
{
    int i = 0;
    int j = 0;
    while (s1[i] != '\0')
    {
        char c1 = s1[i];
        char c2 = s1[i + 1];
        char c3 = s1[i + 2];
        if (c2 == '-' && (isdigit(c1) && isdigit(c3) || islower(c1) && islower(c3) || isupper(c1) && isupper(c3)))
        {
            if (c1 < c3)
            {
                for (c1; c1 <= c3; c1++)
                {
                    s2[j++] = c1;
                }
            }
            else
            {
                for (c1; c1 >= c3; c1--)
                {
                    s2[j++] = c1;
                }
            }
            i += 3;
        }
        else
        {
            s2[j++] = s1[i++];
        }
    }
    s2[j] = '\0';
}