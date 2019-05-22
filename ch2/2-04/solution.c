#include <stdio.h>

#define MAXLINE 1000

void squeeze(char s1[], char s2[]);

int main(void)
{
    char s1[MAXLINE] = "this is a string";
    char s2[MAXLINE] = "ia";
    squeeze(s1, s2);
    puts(s1);
    return 0;
}

/* squeeze: delete chars in s1 that match any chars in s2 */
void squeeze(char s1[], char s2[])
{
    // chars to match
    for (int k = 0; s2[k] != '\0'; k++)
    {
        int i, j;
        // chars in source string
        for (i = j = 0; s1[i] != '\0'; i++)
            // source char matches
            if (s1[i] != s2[k])
                // delete from source string
                s1[j++] = s1[i];
        // terminate after shortening source
        s1[j] = '\0';
    }
}