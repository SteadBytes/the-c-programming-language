#include <stdio.h>
#include <string.h>

#define MAXLINES 5000 /* max #lines to be sorted */

char *lineptr[MAXLINES]; /* pointers to input text lines */
char lines[MAXLINES];

int readlines(char *lineptr[], char *lines, int nlines);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

/* sort input lines alphabetically */
int main(void)
{
    int nlines;
    if ((nlines = readlines(lineptr, lines, MAXLINES)) >= 0)
    {
        /* sort line pointers */
        qsort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
        return 0;
    }
    else
    {
        printf("error: input too large, max lines=%d\n", MAXLINES);
        return 1;
    }
}

#define MAXLEN 1000         /* max length of an input line */
#define MAXLINESTORAGE 5000 /* size of storage space for intput lines */

int get_line(char *s, int lim);

/*
    readlines: read input lines, return line count
    return -1 if input too large
    populates lineptr with pointers to each line
    stores each line in lines array
*/
int readlines(char *lineptr[], char *lines, int maxlines)
{
    char *p = lines;                          /* current line location */
    char *final_loc = lines + MAXLINESTORAGE; /* final memory location */

    int len = 0, nlines = 0;
    char line[MAXLEN];
    while ((len = get_line(line, MAXLEN)) > 0)
    {
        if (nlines >= maxlines || p + len > final_loc)
        {
            return -1;
        }
        else
        {
            line[len - 1] = '\0'; /* remove newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
            p += len;
        }
    }
    return nlines;
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

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
    while (nlines-- > 0)
    {
        puts(*lineptr++);
    }
}

void swap(char *v[], int i, int j);

/* qsort: sort v[left]...v[right] into ascending order */
void qsort(char *v[], int left, int right)
{
    /* do nothing if array contains fewer than 2 elements */
    if (left >= right)
    {
        return;
    }

    swap(v, left, (left + right) / 2);

    int last = left;
    for (int i = left + 1; i <= right; i++)
    {
        if (strcmp(v[i], v[left]) < 0)
        {
            swap(v, ++last, i);
        }
    }
    swap(v, left, last);
    qsort(v, left, last - 1);
    qsort(v, last + 1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j)
{
    char *tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
}