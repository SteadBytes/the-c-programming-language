#include <stdio.h>

int strrindex(char source[], char searchfor[]);

int main(void)
{
    char line[] = "Ah Love! could you and I with Fate conspire Would";
    char pattern[] = "ould";
    printf("%d\n", strrindex(line, pattern));
}

/* strrindex: return index of rightmost occurrence of t in s -1 if none */
int strrindex(char s[], char t[])
{
    int i, j, k, t_index = -1;
    for (i = 0; s[i] != '\0'; i++)
    {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0')
        {
            t_index = i;
        }
    }
    return t_index;
}