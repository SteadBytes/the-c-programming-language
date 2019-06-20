#include <string.h>
#include "get_token.h"

char out[1000];

/*
    undcl: convert word description to declaration
    word descriptions are represented as symbols:
    "x is a function returning a pointer to an array of pointers to functions
    returning char" -> input = x () * [] * () char
*/
int main(void)
{
    int type;
    char temp[MAXTOKEN];

    while (get_token() != EOF)
    {
        strcpy(out, token);
        while ((type = get_token()) != '\n')
        {
            if (is_brackets(type))
            {
                strcat(out, token);
            }
            else if (type == '*')
            {
                /* ex 5-19: don't print redundant parentheses */
                type = peek_token();
                if (is_brackets(type))
                {
                    sprintf(temp, "(*%s)", out);
                }
                else
                {
                    sprintf(temp, "*%s", out);
                }
                strcpy(out, temp);
            }
            else if (type == NAME)
            {
                sprintf(temp, "%s %s", token, out);
                strcpy(out, temp);
            }
            else
            {
                printf("invalid input at %s\n", token);
            }
        }
        printf("%s\n", out);
    }
    return 0;
}