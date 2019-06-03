#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "calc.h"

#define MAXOP 100
#define MAXVARIABLES 26 /* number of supported variables */

int strequal(char s[], char t[]);
void handle_math_func(char s[]);
void displayop(double op);

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

/* streqal: return 1 if s is equal to t */
int strequal(char s[], char t[])
{
    return strcmp(s, t) == 0;
}