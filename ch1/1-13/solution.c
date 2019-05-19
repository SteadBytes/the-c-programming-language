#include <stdio.h>

#define MAX_WORD_LEN 20
#define HIST_SCALE 15 /* height to always display highest frequency word  with */
#define IN 1
#define OUT 0

main()
{
    int c, state, curr_len, out_of_range, max_len;
    state = OUT;
    curr_len = out_of_range = max_len = 0;

    int freqs[MAX_WORD_LEN];
    for (int i = 0; i < MAX_WORD_LEN; ++i)
    {
        freqs[i] = 0;
    }

    while ((c = getchar()) != EOF)
    {
        if (c == ' ' || c == '\n' || c == '\t')
        {
            state = OUT;
            if (curr_len > 0)
            {
                /* end of word encountered */
                if (curr_len < MAX_WORD_LEN)
                {
                    ++freqs[curr_len];
                }
                else
                {
                    ++out_of_range;
                }
            }
            /* track maximum encountered length for display scaling */
            if (curr_len > max_len)
            {
                max_len = curr_len;
            }
            curr_len = 0;
        }
        /* start of word encountered */
        else if (state == OUT)
        {
            state = IN;
            curr_len = 1;
        }
        /* next char of current word encountered */
        else
        {
            ++curr_len;
        }
    }

    int scaled_len;
    for (int i = 0; i < MAX_WORD_LEN; i++)
    {
        printf("%2d - %2d| ", i, freqs[i]);
        if (freqs[i] > 0)
        {
            /* scale frequency so largest value is printed as HIST_SCALE units */
            scaled_len = (freqs[i] * HIST_SCALE) / max_len;
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
        printf("%d words were larger than the maximum %d\n", out_of_range, MAX_WORD_LEN);
    }
}