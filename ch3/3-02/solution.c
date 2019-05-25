#include <stdio.h>

#define MAXLINE 1000

void escape(char s[], char t[]);
void unescape(char s[], char t[]);

int main(void)
{
    char s[MAXLINE];
    char t[MAXLINE] = "ab\ncd\tef\ngh\tij\n";
    escape(s, t);
    puts(s);
    unescape(t, s);
    puts(t);
    return 0;
}

/* escape: copy t to s, converting \n and \t into visible escape sequences */
void escape(char s[], char t[])
{
    int j = 0;
    for (int i = 0; t[i] != '\0'; i++, j++)
    {
        switch (t[i])
        {
        case '\n':
            s[j++] = '\\';
            s[j] = 'n';
            break;
        case '\t':
            s[j++] = '\\';
            s[j] = 't';
            break;
        default:
            s[j] = t[i];
            break;
        }
    }
    s[j] = '\0';
}

/* unescape: copy t to s, unescaping \\n and \\t escape sequences */
void unescape(char s[], char t[])
{
    int j = 0;
    for (int i = 0; t[i] != '\0'; i++, j++)
    {
        if (t[i] != '\\')
        {
            s[j] = t[i];
        }
        else
        {
            switch (t[++i])
            {
            case 'n':
                s[j] = '\n';
                break;
            case 't':
                s[j] = '\t';
                break;
            default:
                s[j] = '\\';
                s[j] = s[i];
                break;
            }
        }
    }
    s[j] = '\0';
}