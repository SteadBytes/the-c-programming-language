#include <stdio.h>
#include <string.h>
#include "get_token.h"

void dcl(void);
void dirdcl(void);

char name[MAXTOKEN];     /* identifier */
char datatype[MAXTOKEN]; /* C data type of declaration i.e. int */
char out[1000];

/* convert declaration to words */
int main(void)
{
    while (get_token() != EOF)
    {
        strcpy(datatype, token); /* 1st token on line = datatype */
        out[0] = '\0';
        dcl(); /* parse remainder of line */
        if (token_type != '\n')
        {
            puts("syntax error");
            return 1;
        }
        printf("%s: %s %s\n", name, out, datatype);
    }
    return 0;
}

/* dcl: parse a declarator */
void dcl(void)
{
    int ns;
    /* count '*' characters */
    for (ns = 0; get_token() == '*';)
    {
        ns++;
    }
    dirdcl();
    while (ns-- > 0)
    {
        strcat(out, " pointer to");
    }
}

/* dirdcl: parse a direct declarator */
void dirdcl(void)
{
    if (token_type == '(')
    { /* ( dcl ) */
        dcl();
        if (token_type != ')')
        {
            handle_parse_err("error: missing )");
        }
    }
    else if (token_type == NAME)
    { /* var name */
        strcpy(name, token);
    }
    else
    {
        handle_parse_err("error: expected name or (dcl)");
    }

    int type;
    while (is_brackets((type = get_token())))
    {
        if (type == PARENS)
        {
            strcat(out, " function returning");
        }
        else
        {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
    }
}