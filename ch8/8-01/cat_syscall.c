#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 1024

/* cat: concatenate files, syscall version*/
int main(int argc, char *argv[])
{
    int fd;
    void filecopy(int, int);
    char *prog = argv[0];

    /* no args -> copy stdin */
    if (argc == 1)
    {
        filecopy(0, 1);
    }
    else
    {
        while (--argc > 0)
        {
            if ((fd = open(*++argv, O_RDONLY, 0)) == -1)
            {
                fprintf(stderr, "%s: can't open %s\n", prog, *argv);
                exit(1);
            }
            else
            {
                filecopy(fd, 1);
                close(fd);
            }
        }
    }
    if (ferror(stdout))
    {
        fprintf(stderr, "%s: error writing to stdout\n", prog);
        exit(2);
    }
    exit(0);
}

/* filecopy : copy file ifp to file ofp */
void filecopy(int ifd, int ofd)
{
    char buf[BUFSIZE];
    int n;
    while ((n = read(ifd, buf, BUFSIZE)) > 0)
    {
        write(ofd, buf, n);
    }
}