#include <stdio.h>
#include "tabs.h"

#define MAXLINE 1000 /* maximum input line length */

void entab(char *tabs);

/*
    replace strings of blanks in input by minimum number of tabs and blanks to
    achieve the same spacing.

    Method: 
    read list of tab stops from args
        -> use default TAB_WIDTH if not given
    store tab stop positions in 'boolean' array of line positions
        -> tabs[i] == 1 if tab stop else 0
    Read chars from input, replace strings of blanks with tabs according to tabs array
*/
int main(int argc, char *argv[])
{
    char tabs[MAXLINE + 1];
    init_tabs(argc, argv, tabs);
    entab(tabs);
    return 0;
}

/*
    entab: replace strings of blanks from stdin with the minimum
    number of tabs and spaces to achieve the same spacing in stdout
*/
void entab(char *tabs)
{
    int c;
    int n_blanks = 0, n_tabs = 0;
    for (int line_pos = 1; (c = getchar()) != EOF; line_pos++)
    {
        if (c == ' ')
        {
            if (is_tab_stop(line_pos, tabs))
            {
                /* at a tab stop -> replace blanks w/tabs */
                n_blanks = 0;
                ++n_tabs;
            }
            else
            {
                /* not at a tab stop -> leave blanks */
                n_blanks++;
            }
        }
        else
        {
            for (; n_tabs > 0; n_tabs--)
            {
                putchar('\t'); /* output required tabs */
            }
            if (c == '\t')
            {
                /* leave original tab -> reset required blanks */
                n_blanks = 0;
            }
            else
            {
                for (; n_blanks > 0; n_blanks--)
                {
                    putchar(' '); /* output required blanks */
                }
            }
            putchar(c);
            if (c == '\n')
            {
                /* new line -> reset position in line */
                line_pos = 0;
            }
            else if (c == '\t')
            {
                /* move to next tab stop */
                while (!is_tab_stop(line_pos, tabs))
                {
                    ++line_pos;
                }
            }
        }
    }
}