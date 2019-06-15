#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINES 5000    /* max # input lines to sort */
char *lineptr[MAXLINES]; /* pointers to input text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines, int reverse);

void q_sort(void *lineptr[], int left, int right,
            int (*comp)(void *, void *));
/* const char to match string.h strcmp for pointer conversion in main */
int numcmp(const char *s1, const char *s2);
int str_casecmp(const char *s1, const char *s2);

/*
    sort input lines into ascending order
    -n option = numerical sort
    -r option = reverse (descending) sort
    -f option = fold upper and lower case together (case insensitive sort)
*/
int main(int argc, char *argv[])
{
    /* read options */
    int reverse = 0, numeric = 0, fold = 0;
    while (--argc > 0 && (*++argv)[0] == '-')
    {
        int c;
        while (c = *++argv[0])
        {
            switch (c)
            {
            case 'n':
                numeric = 1;
                break;
            case 'r': /* ex 5-14 */
                reverse = 1;
                break;
            case 'f': /* ex 5-15 */
                fold = 1;
                break;
            default:
                printf("error: invalid option: %c\n", c);
                return 1;
            }
        }
    }
    /* read input, sort and output */
    int nlines;
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0)
    {

        /* determine sorting function based on options */
        int (*sortfn)(void *, void *);
        if (numeric)
        {
            sortfn = (int (*)(void *, void *))numcmp;
        }
        else if (fold)
        {
            sortfn = (int (*)(void *, void *))str_casecmp;
        }
        else
        {
            sortfn = (int (*)(void *, void *))strcmp;
        }
        q_sort((void **)lineptr, 0, nlines - 1, sortfn);
        writelines(lineptr, nlines, reverse);
        return 0;
    }
    else
    {
        printf("input too large to sort, max lines = %d\n", MAXLINES);
        return 1;
    }
}

/*
    q_sort: sort v[left]...v[right] into ascending order
    renamed to avoid conflict with stdlib qsort
 */
void q_sort(void *v[], int left, int right,
            int (*comp)(void *, void *))
{
    void swap(void *v[], int, int);
    if (left >= right)
    {
        return;
    }
    swap(v, left, (left + right) / 2);
    int last = left;
    for (int i = left + 1; i <= right; i++)
    {
        if ((*comp)(v[i], v[left]) < 0)
        {
            swap(v, ++last, i);
        }
    }
    swap(v, left, last);
    q_sort(v, left, last - 1, comp);
    q_sort(v, last + 1, right, comp);
}

/* numpcmp: compare strings s1 and s2 numerically */
int numcmp(const char *s1, const char *s2)
{
    double v1 = atof(s1), v2 = atof(s2);
    if (v1 < v2)
    {
        return -1;
    }
    else if (v1 > v2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*
    str_casecmp: case-insensitive compare strings s1 and s2
    implementation of *nix C strcasecmp non-standard function
*/
int str_casecmp(const char *s1, const char *s2)
{
    while (tolower(*s1) == tolower(*s2++))
    {
        if (*s1++ == '\0')
        {
            return 0;
        }
    }
    return tolower(*s1) - tolower(*--s2);
}

void swap(void *v[], int i, int j)
{
    void *tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
}

#define MAXLEN 1000         /* max length of an input line */
#define MAXLINESTORAGE 5000 /* size of storage space for intput lines */

int get_line(char *s, int lim);

/*
    readlines: read input lines, return line count
    return -1 if input too large
    populates lineptr with pointers to each line
*/
int readlines(char *lineptr[], int maxlines)
{

    int len = 0, nlines = 0;
    char *p, line[MAXLEN];
    while ((len = get_line(line, MAXLEN)) > 0)
    {
        if (nlines >= maxlines || (p = malloc(len)) == NULL)
        {
            return -1;
        }
        else
        {
            line[len - 1] = '\0'; /* remove newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
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
void writelines(char *lineptr[], int nlines, int reverse)
{
    if (reverse)
    {
        for (int i = nlines - 1; i >= 0; i--)
        {
            puts(lineptr[i]);
        }
    }
    else
    {
        for (int i = 0; i < nlines; i++)
        {
            puts(lineptr[i]);
        }
    }
}
