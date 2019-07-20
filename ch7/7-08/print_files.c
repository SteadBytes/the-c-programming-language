#include <stdio.h>

#define MAXLINE 1000
#define MAXPAGELINES 100
#define HEADERPADDING 2

int print_file(FILE *fp, char *fname);

/*
    print_files: print set of files, starting each on a new page, with a
    running page count for each file,
*/
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: print_files [FILE]...\n");
    }
    char *prog = argv[0];

    while (--argc > 0)
    {
        char *fname = *++argv;
        FILE *fp = fopen(fname, "r");
        if (fp == NULL)
        {
            fprintf(stderr, "%s: can't open %s\n", prog, fname);
            return 1;
        }
        print_file(fp, fname);
    }
    return 0;
}

int print_header(char *fname, int total_pages);
int print_file(FILE *fp, char *fname)
{
    int line_num;
    int total_pages = 1;
    char line[MAXLINE];
    while (fgets(line, MAXLINE, fp) != NULL)
    {
        /* start new page */
        if (line_num == 1)
        {
            fprintf(stdout, "\f");
            line_num = print_header(fname, total_pages++);
        }
        fputs(line, stdout);
        /* page line limit reached */
        if (++line_num > MAXPAGELINES)
        {
            line_num = 1; /* reset to start new page on next iteration */
        }
    }
    fprintf(stdout, "\f"); /* finish file with new page */
}

int print_header(char *fname, int total_pages)
{
    int lines = 0;
    /* top padding */
    for (int l; l <= HEADERPADDING; l++, lines++)
    {
        fprintf(stdout, "\n");
    }
    fprintf(stdout, "%s fname   p.%d\n", fname, total_pages); /* 1 line */
    lines++;
    /* bottom padding */
    for (int l; l <= HEADERPADDING; l++, lines++)
    {
        fprintf(stdout, "\n");
    }
    return lines;
}