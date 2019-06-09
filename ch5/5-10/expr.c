#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NUMBER '0'

void push(double);
double pop(void);

/* CLI reverse Polish calculator */
int main(int argc, char *argv[])
{
    if (argc == 1) {
        puts("Usage: expr ARGS\n\te.g. expr 1 2 +");
        return 1;
    }
    double op2;
    while (--argc > 0)
    {
        int c = **++argv;
        int type = !isdigit(c) && strlen(*argv) == 1 ? c : NUMBER;
        switch (type)
        {
        case NUMBER:
            push(atof(*argv));
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
        case '/':
            op2 = pop();
            if (op2 == 0.0)
            {
                puts("error: division by zero");
            }
            else
            {
                push(pop() / op2);
            }
            break;
        default:
            printf("error: unknown command %s\n", *argv);
            break;
        }
    }
    printf("%.8g\n", pop());
    return 0;
}

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

/* push: push f onto value stack */
void push(double f)
{
    if (sp < MAXVAL)
    {
        val[sp++] = f;
    }
    else
    {
        printf("error: stack full, can't push %f\n", f);
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
        printf("error: stack empty\n");
        return 0.0;
    }
}