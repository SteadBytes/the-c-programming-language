#include <stdio.h>

#define MAX_ASCII_VALUE 128
#define HIST_SCALE 15 /* height to always display highest frequency word  with */

main()
{
    int c, max_char, out_of_range;
    max_char = out_of_range = 0;

    int freqs[MAX_ASCII_VALUE];
    for (int i = 0; i < MAX_ASCII_VALUE; ++i)
    {
        freqs[i] = 0;
    }

    while ((c = getchar()) != EOF)
    {
        if (c >= 0 && c < MAX_ASCII_VALUE)
        {
            ++freqs[c];

            if (c > max_char)
            {
                max_char = c;
            }
        }
        else
        {
            ++out_of_range;
        }
    }

    int scaled_len;
    for (int i = 0; i < MAX_ASCII_VALUE; i++)
    {
        printf("%d (%c) - %2d| ", i, i, freqs[i]);
        if (freqs[i] > 0)
        {
            /* scale frequency so largest value is printed as HIST_SCALE units */
            scaled_len = (freqs[i] * HIST_SCALE) / max_char;
            if (scaled_len <= 0)
            {
                /* scaling may produce decimal values -> display as 1 unit */
                scaled_len = 1;
            }
        }
        else
        {
            scaled_len = 0;
        }

        while (scaled_len > 0)
        {
            putchar('*');
            --scaled_len;
        }
        putchar('\n');
    }

    if (out_of_range > 0)
    {
        printf("%d chars were not in ASCII value range 0-%d\n", out_of_range, MAX_ASCII_VALUE);
    }
}