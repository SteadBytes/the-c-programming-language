#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_N 10
#define MAXLINES 100 /* max # of input lines to store */
#define MAXLEN 1000  /* max input line length */

int get_line(char *s, int lim);

/* 
    tail: print the last n (default 10) lines of input
    -n option to specify value for n
    behave *rationally* no matter how unreasonable the input or n
    make best use of available storage
    set value of n to -n arg if present else 10
    initialise array of n char pointers to store input lines
    readlines into line pointers array
    output each line referenced by line pointers array
*/
int main(int argc, char *argv[])
{
    int n = (argc == 2 && *argv[1] == '-') ? atoi(&(*++argv)[1]) : DEFAULT_N;
    if (n < 1 || n > MAXLINES)
    {
        printf("warning: n not in range 1<=n<=%d, using default %d\n", MAXLINES, DEFAULT_N);
        n = DEFAULT_N;
    }

    char *p, *lines;
    if ((p = lines = malloc(MAXLEN * MAXLINES)) == NULL)
    {
        printf("error: unable to allocate memory for line storage");
        return -1;
    }
    char *lines_end = lines + MAXLINES * MAXLEN;

    char *lineptr[MAXLINES];
    char line[MAXLEN];
    int len, nlines = 0, l_index = 0;
    while ((len = get_line(line, MAXLEN)) > 0)
    {
        /*
            wrap around and re-use lines array -> enable reading large inputs
            without allocating more memory
        */
        if (p + len + 1 >= lines_end)
        {
            p = lines;
        }
        line[len - 1] = '\0'; /* remove newline */
        lineptr[l_index] = p;
        strcpy(lineptr[l_index], line);
        /*
            wrap around and re-use lineptr elements -> enable reading large inputs
            without allocating more memory
        */
        if (++l_index >= MAXLINES)
        {
            l_index = 0;
        }
        p += len + 1;
        nlines++;
    }

    /* ensure # of lines requested by user is <= # of lines actually read */
    if (n > nlines)
    {
        n = nlines;
    }
    /* first line to print out -> nth from last line */
    int start_index = l_index - n;
    /* # lines read > MAXLINES -> adjust index of nth from last line */
    if (start_index < 0)
    {
        start_index += MAXLINES;
    }
    /*
        print last n lines read
        start_index may wrap around -> mod ensures 0<=i<=MAXLINES-1
    */
    for (int i = start_index; n-- > 0; i = (i + 1) % MAXLINES)
    {
        puts(lineptr[i]);
    }
    return 0;
}

/* get_line: read a line into s, return length
    (underscore to prevent collision w/stdio) */
int get_line(char *s, int lim)
{
    /* save start address to calculate length */
    char *start = s;
    /* read chars into s from stdin */
    int c;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
    {
        *s++ = c;
    }
    /* include newline if present */
    if (c == '\n')
    {
        *s++ = c;
    }
    *s = '\0';
    return s - start;
}