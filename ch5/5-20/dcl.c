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
    void parameter_dcl(void);

    if (token_type == '(')
    { /* ( dcl ) */
        dcl();
        if (token_type != ')')
        {
            handle_parse_err("error: missing )");
        }
    }
    else if (token_type == NAME) /* var name */
    {
        /* ensure name isn't copied multiple times */
        if (name[0] == '\0')
        {
            strcpy(name, token);
        }
    }
    else /* token can't be used yet - further parsing needed -> push back */
    {
        token_available = 1;
    }

    int type;
    while (is_brackets((type = get_token())) || type == '(')
    {
        if (type == PARENS)
        {
            strcat(out, " function returning");
        }
        else if (type == '(')
        {
            strcat(out, " function taking");
            parameter_dcl();
            strcat(out, " returning");
        }
        else
        {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
    }
}

void parameter_dcl(void)
{
    void specification(void);
    do
    {
        specification();
    } while (token_type == ',');
    if (token_type != ')')
    {
        handle_parse_err("error: missing )");
    }
}

void specification(void)
{
    int type(void);
    int qualifier(void);

    char tmp[MAXTOKEN];
    tmp[0] = '\0';

    get_token();
    do
    {
        /* new declaration */
        if (token_type != NAME)
        {
            token_available = 1;
            dcl();
        }
        else if (type() || qualifier())
        {
            strcat(tmp, " ");
            strcat(tmp, token);
            get_token();
        }
        else
        {
            handle_parse_err("error: parameter list contains unknown type");
        }
    } while (token_type != ',' && token_type != ')'); /* until next param of end of params */
    strcat(out, tmp);
    /* more params present */
    if (token_type == ',')
    {
        strcat(out, ",");
    }
}

int strequal(char *s1, char *s2);

/* type: return 1 if token is a valid type else 0 */
int type(void)
{
    return strequal(token, "void") ||
           strequal(token, "char") ||
           strequal(token, "int") ||
           strequal(token, "float") ||
           strequal(token, "double");
}

/* qualifier: return 1 if token is a valid qualifier else 0 */
int qualifier(void)
{
    return strequal(token, "const") ||
           strequal(token, "volatile") ||
           strequal(token, "restrict");
}

/* streqal: return 1 if s1 is equal to s2 */
int strequal(char *s1, char *s2)
{
    return strcmp(s1, s2) == 0;
}