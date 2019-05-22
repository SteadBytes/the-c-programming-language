#include <stdio.h>

#define MAXLINE 1000

int any(char s1[], char s2[]);

int main(void)
{
    char s1[MAXLINE] = "this is a string";
    char s2[MAXLINE] = "ia";
    printf("First index of s1 containing a char in s2: %d\n", any(s1, s2));
    return 0;
}

/* any: return the first index of s1 containing a character from s2
    return -1 if s1 contains no characters from s2 */
int any(char s1[], char s2[])
{
    for (int i = 0; s1[i] != '\0'; i++)
    {
        for (int j = 0; s2[j] != '\0'; j++)
        {
            if (s1[i] == s2[j])
            {
                return i;
            }
        }
    }
    return -1;
}
