#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100  /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */

int getop(char[]);
void push(double);
double pop(void);

/* reverse Polish calculator */
int main(void)
{
    int type;
    /* 
        non-commutative operators use intermediate variable to store
        first operand to ensure correct order
    */
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF)
    {
        switch (type)
        {
        case NUMBER:
            push(atof(s));
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
        case '\n':
            printf("\t%.8g\n", pop());
            break;
        default:
            printf("error unknown command %s\n", s);
            break;
        }
    }
    return 0;
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

#include <ctype.h>

int getch(void);
void ungetch(int);

/* getop: get next operator or numeric operand */
int getop(char s[])
{
    int i, c, c2;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
    {
        ;
    }
    s[1] = '\0';
    if (!isdigit(c) && c != '.' && c != '-')
    {
        return c; /* not a number */
    }

    i = 0;
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

char buf[BUFSIZE]; /* ungetch buffer */
int bufp = 0;      /* next free position in buf */

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