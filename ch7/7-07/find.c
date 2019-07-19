#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

void pattern_search(FILE *fp, char *fname, char *pattern, int except, int number);

/*
    find: print lines that match pattern from 1st arg. Reads input from named
    files if present else stdin
*/
int main(int argc, char *argv[])
{
    char *prog = argv[0];
    int c, except = 0, number = 0;

    /* process options */
    while (--argc > 0 && (*++argv)[0] == '-')
    {
        while (c = *++argv[0])
        {
            switch (c)
            {
            case 'x':
                except = 1;
                break;
            case 'n':
                number = 1;
                break;
            default:
                fprintf(stderr, "%s: illegal option %c\n", prog, c);
                return 1;
            }
        }
    }

    /* no pattern provided */
    if (argc < 1)
    {
        fprintf(stderr, "Usage: %s [-x] [-n] PATTERN [FILE]...\n", prog);
        return 1;
    }

    char pattern[MAXLINE];
    strcpy(pattern, *argv);

    if (argc == 1)
    {
        /* no named files -> read and search stdin */
        pattern_search(stdin, "", pattern, except, number);
    }
    else
    {
        /* named files -> read and search each in turn */
        while (--argc > 0)
        {
            char *fname = *++argv;
            FILE *fp = fopen(fname, "r");
            if (fp == NULL)
            {
                fprintf(stderr, "%s can't open %s\n", prog, fname);
                return 1;
            }
            pattern_search(fp, fname, pattern, except, number);
            fclose(fp);
        }
    }
}

/* pattern_search: search for pattern in file fname */
void pattern_search(FILE *fp, char *fname, char *pattern, int except, int number)
{
    char line[MAXLINE];
    long lineno = 0;
    while (fgets(line, MAXLINE, fp) != NULL)
    {
        lineno++;
        if ((strstr(line, pattern) != NULL) != except)
        {
            if (*fname)
            {
                printf("%s - ", fname);
            }
            if (number)
            {
                printf("%ld:", lineno);
            }
            printf("%s", line);
        }
    }
}