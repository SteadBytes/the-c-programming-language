#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

#define MAX_CUR_FMT 100
void minprintf(char *, ...);

int main(void)
{
    minprintf("%d, %f, %s, %c, %u\n", 1, 1.5, "hello", 'c', 1);
}

/* minprintf: minimal printf with variable argument list */
void minprintf(char *fmt, ...)
{
    va_list ap;        /* pointer to each unnamed arg in turn */
    va_start(ap, fmt); /* make ap point to 1st unnamed arg */
    for (char *p = fmt; *p; p++)
    {
        if (*p != '%') /* no formatting */
        {
            putchar(*p);
            continue;
        }

        /*
        collect single format specification up to format letter
        i.e. "%10.10f" -> "%10.10"
        */
        char cur_fmt[MAX_CUR_FMT];
        int i = 0;
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
        cur_fmt passed to printf along with fetched arg to do actual formatting
        */
        switch (*++p)
        {
        case 'c':
        case 'i':
        case 'd':;
            int ival = va_arg(ap, int);
            printf(cur_fmt, ival);
            break;
        case 'o':
        case 'x':
        case 'X':
        case 'u':;
            unsigned uval = va_arg(ap, unsigned);
            printf(cur_fmt, uval);
            break;
        case 'f':;
            double dval = va_arg(ap, double);
            printf(cur_fmt, dval);
            break;
        case 's':;
            char *sval = va_arg(ap, char *);
            printf(cur_fmt, sval);
            break;
        default:;
            putchar(*p);
            break;
        }
    }
    va_end(ap); /* clean up when done */
}