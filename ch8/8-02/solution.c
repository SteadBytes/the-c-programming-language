#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

#define OPEN_MAX 20
#define PERMS 0666 /* RW for owner, group, others */

struct _flags
{
    unsigned read : 1;
    unsigned write : 1;
    unsigned unbuf : 1;
    unsigned buf : 1;
    unsigned eof : 1;
    unsigned err : 1;
};

typedef struct _iobuf
{
    int cnt;
    char *ptr;
    char *base;
    struct _flags flags;
    int fd;
} FILE;

FILE _iob[OPEN_MAX];

/* fopen: open file, return file pointer */
FILE *fopen(char *name, char *mode)
{
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
    {
        return NULL;
    }
    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
    {
        if ((fp->flags.read == 0 && fp->flags.write == 0))
        {
            break; /* free slot */
        }
    }
    if (fp >= _iob + OPEN_MAX)
    {
        /* no free slots in buffer */
        return NULL;
    }

    if (*mode == 'w')
    {
        fd = creat(name, PERMS);
    }
    else if (*mode == 'a')
    {
        if ((fd = open(name, O_WRONLY, 0)) == -1)
        {
            fd = creat(name, PERMS);
        }
        lseek(fd, 0L, 2);
    }
    else
    {
        fd = open(name, O_RDONLY, 0);
    }

    if (fd == -1)
    {
        return NULL;
    }
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flags.unbuf = 0;
    fp->flags.buf = 1;
    fp->flags.eof = 0;
    fp->flags.err = 0;
    if (*mode == 'r')
    {
        fp->flags.read = 1;
        fp->flags.write = 0;
    }
    else
    {
        fp->flags.read = 0;
        fp->flags.write = 1;
    }
    return fp;
}

/* _fillbuf: allocate and fill input buffer */
int _fillbuf(FILE *fp)
{
    int bufsize;

    /* file not open for reading */
    if ((fp->flags.read == 0 || fp->flags.eof == 1 || fp->flags.err == 1))
    {
        return EOF;
    }
    bufsize = (fp->flags.unbuf == 1) ? 1 : BUFSIZ;
    if (fp->base == NULL) /* no buffer initialised for this file yet */
    {
        if ((fp->base = (char *)malloc(bufsize)) == NULL)
        {
            return EOF;
        }
    }
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0)
    {
        if (fp->cnt == -1)
        {
            fp->flags.eof == 1;
        }
        else
        {
            fp->flags.err == 1;
        }
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char)*fp->ptr++;
}