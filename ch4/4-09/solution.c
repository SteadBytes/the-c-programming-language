#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#define MAXOP 100       /* max size of operand or operator */
#define MAXVARIABLES 26 /* number of supported variables */
#define NUMBER '0'      /* signal that a number was found */
#define FUNCTION 'f'    /* signal that a named function */

int getop(char[]);
void push(double);
double pop(void);
void clear(void);
void displayop(double op);
int strequal(char s[], char t[]);
void handle_math_func(char s[]);

/* reverse Polish calculator */
int main(void)
{
    int type, last_type = 0;
    /* 
        non-commutative operators use intermediate variable to store
        first operand to ensure correct order
    */
    double op, op2, last_val;
    char s[MAXOP];

    double variables[MAXVARIABLES];
    for (int i = 0; i < MAXVARIABLES; i++)
    {
        variables[i] = 0.0;
    }

    while ((type = getop(s)) != EOF)
    {
        switch (type)
        {
        case NUMBER:
            push(atof(s));
            break;
        case FUNCTION:
            /* ex 4-05: access to math library functions */
            handle_math_func(s);
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if (op2 != 0.0)
            {
                push(pop() / op2);
            }
            else
            {
                puts("error: zero divisor");
            }
            break;
        case '%':
            /* ex 4-03 */
            op2 = pop();
            push((int)pop() % (int)op2);
            break;
        case '=':
            pop();
            /* ex 4-06: assign value to variable */
            if (isupper(last_type))
            {
                variables[last_type - 'A'] = pop();
            }
            else
            {
                printf("error: assignment without variable name");
            }
            break;
        case '?':
            /* ex 4-04: print top of stack without popping */
            op2 = pop();
            displayop(op2);
            push(op2);
            break;
        case 'd':
            /* ex 4-04: duplicate top element of stack */
            op2 = pop();
            push(op2);
            push(op2);
            break;
        case 's':
            /* ex 4-04: swap top two elements of stack */
            op = pop();
            op2 = pop();
            push(op);
            push(op2);
            break;
        case 'c':
            /* ex 4-04: clear stack */
            clear();
            break;
        case '\n':
            /* ex 4-06: variable to hold last value */
            last_val = pop();
            displayop(last_val);
            break;
        default:
            /* ex 4-06: push value of variable onto stack */
            if (isupper(type))
            {
                push(variables[type - 'A']);
            }
            else if (type == 'v')
            {
                /* ex 4-06: variable to hold last value */
                push(last_val);
            }
            else
            {

                printf("error unknown command %s\n", s);
            }
            break;
        }
        last_type = type;
    }
    return 0;
}

void displayop(double op)
{
    printf("\t%.8g\n", op);
}

/* streqal: return 1 if s is equal to t */
int strequal(char s[], char t[])
{
    return strcmp(s, t) == 0;
}

/* handle_math_func: ex 4-05: apply supported function from math library*/
void handle_math_func(char s[])
{
    if (strequal(s, "sin"))
    {
        push(sin(pop()));
    }
    else if (strequal(s, "exp"))
    {
        push(exp(pop()));
    }
    else if (strequal(s, "pow"))
    {
        double exponent = pop();
        push(pow(pop(), exponent));
    }
    else
    {
        printf("error: unsupported operation %s\n", s);
    }
}

#define MAXVAL 100 /* maximum depth of val stack */

int sp = 0;         /* next free stack position */
double val[MAXVAL]; /* value stack */

/* push: push f onto value stack */
void push(double f)
{
    if (sp < MAXVAL)
    {
        val[sp++] = f;
    }
    else
    {
        printf("error: stack full, can't push %g\n", f);
    }
}

/* pop: pop and return top value from stack */
double pop(void)
{
    if (sp > 0)
    {
        return val[--sp];
    }
    else
    {
        puts("error: stack empty");
        return 0.0;
    }
}

/* clear: clear the stack (reset stack pointer) */
void clear(void)
{
    sp = 0;
}

int getch(void);
void ungetch(int);
void ungets(char s[]);

/* getop: get next operator,function or numeric operand */
int getop(char s[])
{
    int i, c, c2;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
    {
        ;
    }
    s[1] = '\0';
    i = 0;
    if (islower(c)) /* ex 4-05: command or FUNCTION */
    {
        while (islower(s[++i] = c = getch()))
        {
            ;
        }
        s[i] = '\0';
        if (c != EOF)
        {
            ungetch(c);
        }
        if (strlen(s) > 1)
        {
            return FUNCTION; /* FUNCTION i.e. sin, cos, pow etc */
        }
        else
        {
            /* command i.e. d to duplicate top stack item or  ex 4-06 variable */
            return isalpha(c) ? c : s[i - 1];
        }
    }
    if (!isdigit(c) && c != '.' && c != '-')
    {
        return c; /* not a number */
    }

    if (c == '-') /*ex 4-03 */
    {
        c2 = getch();
        if (c2 != EOF)
        {
            ungetch(c2);
        }
        if (!isdigit(c2) && c2 != '.')
        {
            return c;
        }
    }
    if (isdigit(c) || c == '-') /* ex 4-03 */
    {                           /* collect integer part */
        while (isdigit(s[++i] = c = getch()))
        {
            ;
        }
    }
    if (c == '.')
    { /* collect fraction part */
        while (isdigit(s[++i] = c = getch()))
        {
            ;
        }
    }
    s[i] = '\0';
    if (c != EOF)
    {
        ungetch(c);
    }
    return NUMBER;
}

#define BUFSIZE 100

/*
    ex 4-09: handle pushed back EOF
    buf was previously a char array. When EOF (int -1) is converted to a char
    the resulting value may be different between C implementations. Some may
    produce 255, others may produce -1. Changing buf to an int array will
    overcome this as no conversion is necessary.
 */
int buf[BUFSIZE]; /* ungetch buffer */
int bufp = 0;     /* next free position in buf */

/* getch: get a (possibly pushed back) character */
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* ungetch: push character back on input */
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
    {
        puts("ungetch: too many characters");
    }
    else
    {
        buf[bufp++] = c;
    }
}