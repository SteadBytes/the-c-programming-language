#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000 /* maximum input line length */
#define TAB_WIDTH 4

/*
    init_tabs: set tab stop positions in array tabs using user provided
    args or according to default TAB_WIDTH if not specified
*/
int init_tabs(int argc, char *argv[], char *tabs)
{
    /* no tab stops provided -> use default */
    if (argc <= 1)
    {
        for (int i = 1; i < MAXLINE; i++)
        {
            tabs[i] = i % TAB_WIDTH == 0;
        }
    }
    else
    {
        /* use tab stops provided by user */
        for (int i = 1; i < MAXLINE; i++)
        {
            tabs[i] = 0;
        }
        while (--argc > 0)
        {
            int tab_stop = atoi(*++argv);
            if (tab_stop > 0 && tab_stop <= MAXLINE)
            {
                tabs[tab_stop] = 1;
            }
            else
            {
                printf("error: expected tab stop in range 0 %d, go %d\n", MAXLINE, tab_stop);
            }
        }
    }
}

int is_tab_stop(int pos, char *tabs)
{
    return tabs[pos] || pos >= MAXLINE;
}