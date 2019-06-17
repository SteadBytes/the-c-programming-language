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
int str_cmp(const char *s1, const char *s2);
int ctoi(const char s);
const char *substr(const char *s, int i, int j);

void err_exit(char *msg, int status);

/* option flags */
int reverse = 0, numeric = 0, fold = 0, directory = 0;
int start = 0, end = 0;
/*
    sort input lines into ascending order
    usage: sort -nrfd -ki[.j]
    options:
    -n = numerical sort
    -r = reverse (descending) sort
    -f = fold upper and lower case together (case insensitive sort)
    -d = directory order sort (compare only letters, numbers and blanks)
    -ki[.j]= sort based on a field within lines. start position=i
        end position defaults to end of line, else specify with j.
        i.e. sort -k3 -> sort based on field between position 3 and end of line
             sort -k3.6 -> sort based on field from position 3 to position 6
        First character in line = position 1
*/
int main(int argc, char *argv[])
{
    /* read options */
    while (--argc > 0 && (*++argv)[0] == '-')
    {
        int c, move_to_next_arg = 0;
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
            case 'd': /* ex 5-16 */
                directory = 1;
                break;
            case 'k': /* ex 5-17 */
                /* TODO: split string on '.' and use atoi on each part? */
                ++argv[0];
                for (; isdigit(*argv[0]); ++argv[0])
                {
                    start = 10 * start + ctoi(*argv[0]);
                }
                if (start <= 0)
                {
                    err_exit("sort: -ki[.j] expected i > 0\n", 1);
                }
                if (*argv[0] == '.')
                {
                    ++argv[0];
                    for (; isdigit(*argv[0]); ++argv[0])
                    {
                        end = 10 * end + ctoi(*argv[0]);
                    }
                    if (end < 0)
                    {
                        err_exit("sort: -ki[.j] expected j > 0\n", 1);
                    }
                }
                if (end && start > end)
                {
                    err_exit("sort: -ki[.j] expected j > i\n", 1);
                }
                move_to_next_arg = 1;
                break;
            default:;
                char msg[80];
                sprintf(msg, "sort: invalid option: %c\n", c);
                err_exit(msg, 1);
            }
            /*
                TODO: Find a better way to handle this
                -k option is multiple chars, where others are single char
             */
            if (move_to_next_arg)
            {
                break;
            }
        }
    }
    /* read input, sort and output */
    int nlines;
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0)
    {
        q_sort((void **)lineptr, 0, nlines - 1,
               (int (*)(void *, void *))(numeric ? numcmp : str_cmp));
        writelines(lineptr, nlines, reverse);
        return 0;
    }
    else
    {
        char msg[80];
        sprintf(msg, "sort: input too large, max lines = %d\n", MAXLINES);
        err_exit(msg, 1);
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

int ctoi(const char c)
{
    return c - '0';
}

const char *substr(const char *s, int i, int j)
{
    if (i == 0 && j >= strlen(s))
    {
        return s;
    }
    if (i > strlen(s))
    {
        err_exit("sort: string too short\n", 1);
    }
    int len = j - i;
    char *subs = malloc(len);
    if (!subs)
    {
        err_exit("sort: unable to allocate memory\n", 1);
    }
    memcpy(subs, s + i, len);
    subs[j - i] = '\0';
    return (const char *)subs;
}

/* numpcmp: compare strings s1 and s2 numerically */
int numcmp(const char *s1, const char *s2)
{
    const char *s1field = start ? substr(s1, start, (end ? end : strlen(s1))) : s1;
    const char *s2field = start ? substr(s2, start, (end ? end : strlen(s2))) : s2;
    double v1 = atof(s1field), v2 = atof(s2field);
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
    next_alphanumeric: returns the difference between s and the index
    containing the next alphanumeric character in s
*/
int next_alphanumeric(const char *s)
{
    const char *start = s;
    while (!isalnum(*s) && *s != ' ' && *s != '\0')
    {
        s++;
    }
    return s - start;
}

/*
    str_cmp: compare strings s1 and s2
    consolidated strcmp an str_casecmp from 5-15 to simplify directory ordering
 */
int str_cmp(const char *s1, const char *s2)
{
    const char *s1field = start ? substr(s1, start, (end ? end : strlen(s1))) : s1;
    const char *s2field = start ? substr(s2, start, (end ? end : strlen(s2))) : s2;
    char c1, c2;
    do
    {
        if (directory)
        {
            s1 += next_alphanumeric(s1field);
            s2 += next_alphanumeric(s2field);
        }
        c1 = fold ? tolower(*s1field++) : *s1field++;
        c2 = fold ? tolower(*s2field++) : *s2field++;
        if (c1 == c2 && c1 == '\0')
        {
            return 0;
        }
    } while (c1 == c2);
    return c1 - c2;
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

/* err_exit: exit program with status, output msg to stderr */
void err_exit(char *msg, int status)
{
    fputs(msg, stderr);
    exit(status);
}