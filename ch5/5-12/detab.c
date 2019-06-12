#include <stdio.h>
#include "tabs.h"

#define MAXLINE 1000 /* maximum input line length */

void detab(char *tabs);

/* replace all tabs in inputs with spaces */
int main(int argc, char *argv[])
{
    char tabs[MAXLINE + 1];
    init_tabs(argc, argv, tabs);
    detab(tabs);
    return 0;
}

/*
    detab: replace tabs in stdin with spaces in stdout
*/
void detab(char *tabs)
{
    int c, line_pos = 1;
    while ((c = getchar()) != EOF)
    {
        if (c == '\t')
        {
            do
            {
                putchar(' ');
            } while (!is_tab_stop(line_pos++, tabs));
        }
        else
        {
            putchar(c);
            if (c == '\n')
            {
                line_pos = 1;
            }
            line_pos = c == '\n' ? 1 : line_pos + 1;
        }
    }
}