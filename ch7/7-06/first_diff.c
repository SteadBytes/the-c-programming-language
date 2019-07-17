#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000

/* compare two files, printing first line where they differ */
int main(int argc, char *argv[])
{
    char *prog = argv[0];
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s FILE1 FILE2", prog);
        exit(1);
    }

    /*
    read and open two filenames from args using above file pointers
    exit(1) and output to stderr if unable to open either file
    */
    char *fname1 = *++argv;
    FILE *fp1 = fopen(fname1, "r");
    if (fp1 == NULL)
    {
        fprintf(stderr, "%s can't open %s\n", prog, fname1);
        exit(1);
    }
    char *fname2 = *++argv;
    FILE *fp2 = fopen(fname2, "r");
    if (fp2 == NULL)
    {
        fprintf(stderr, "%s can't open %s\n", prog, fname2);
        exit(1);
    }
    /*
    read a line from both w/fgets
    compare line w/ strcmp
    if different -> output lines with puts and exit 0 status
    */
    char l1[MAXLINE], l2[MAXLINE];
    char *p1, *p2;

    do
    {
        p1 = fgets(l1, MAXLINE, fp1);
        p2 = fgets(l2, MAXLINE, fp2);
        if (l1 == p1 && l2 != p2)
        {
            if (strcmp(l1, l2) != 0)
            {
                printf("first differing line found in %s\n%s\n", fname1, l1);
                return 0;
            }
        }
        else if (l1 == p1 && l2 != p2)
        {
            printf("%s ended at line\n%s\n", fname2, l2);
            return 0;
        }
        else if (l1 != p1 && l2 == p2)
        {
            printf("%s ended at line\n%s\n", fname1, l1);
            return 0;
        }

    } while (l1 == p1 && l2 == p2);

    return 0;
}