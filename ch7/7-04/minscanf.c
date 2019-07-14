#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

#define MAX_CUR_FMT 100
void minscanf(char *, ...);

int main(void)
{
    int d;
    double f;
    char s[100];
    char c;
    unsigned u;
    char fstring[] = "%d %s %c %u\n";
    /* e.g 1 hello c 100 */
    minscanf(fstring, &d, s, &c, &u);
    printf(fstring, d, s, c, u);
    return 0;
}

/* minscanf: minimal scanf with variable argument list */
void minscanf(char *fmt, ...)
{
    va_list ap;        /* pointer to each unnamed arg in turn */
    va_start(ap, fmt); /* make ap point to 1st unnamed arg */
    /*
    collect single format specification up to format letter
    i.e. "%10.10f" -> "%10.10"
    */
    char cur_fmt[MAX_CUR_FMT];
    int i = 0;
    for (char *p = fmt; *p; p++)
    {
        if (*p != '%') /* not part of format specification */
        {
            cur_fmt[i++] = *p;
            continue; /* move on to next character of format string */
        }

        cur_fmt[i++] = '%';
        while (*(p + 1) && !isalpha(*(p + 1)))
        {
            cur_fmt[i++] = *++p; /* format specification */
        }
        /* add format letter to specification */
        cur_fmt[i++] = *(p + 1);
        cur_fmt[i] = '\0';

        /*
        fetch next unnamed arg based on format letter 
        cur_fmt passed to scanf along with fetched arg to do actual formatting
        */
        switch (*++p)
        {
        case 'c':
        case 'i':
        case 'd':;
            int *ip = va_arg(ap, int *);
            scanf(cur_fmt, ip);
            break;
        case 'o':
        case 'x':
        case 'X':
        case 'u':;
            unsigned *up = va_arg(ap, unsigned *);
            scanf(cur_fmt, up);
            break;
        case 'f':;
            double *dp = va_arg(ap, double *);
            scanf(cur_fmt, dp);
            break;
        case 's':;
            char *sp = va_arg(ap, char *);
            scanf(cur_fmt, sp);
            break;
        default:
            break;
        }
        i = 0; /* end of current format specifier, reset index to collect next */
    }
    va_end(ap); /* clean up when done */
}