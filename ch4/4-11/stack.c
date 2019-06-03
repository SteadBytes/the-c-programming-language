#include <stdio.h>
#include "calc.h"

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