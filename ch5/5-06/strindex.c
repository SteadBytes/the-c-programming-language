#include <stdio.h>

int strindex(char *s, char *t);

int main(void)
{
    char s[] = "this is a sentence";
    char t[] = "this";
    printf("strindex(\"%s\", \"%s\") -> %d\n", s, t, strindex(s, t));

    char t2[] = "sentence";
    printf("strindex(\"%s\", \"%s\") -> %d\n", s, t2, strindex(s, t2));

    char t3[] = "word";
    printf("strindex(\"%s\", \"%s\") -> %d\n", s, t3, strindex(s, t3));
}

/* strindex: return index of t in s, -1 if not present */
int strindex(char *s, char *t)
{
    char *s_start = s;
    for (; *s != '\0'; s++)
    {
        char *j, *k;
        for (j = s, k = t; *k != '\0' && *j == *k; j++, k++)
        {
        }
        if (k > t && *k == '\0')
        {
            return s - s_start;
        }
    }
    return -1;
}