#include <stdio.h>

unsigned invert(unsigned x, int p, int n);

int main(void)
{
    printf("invert(32, 3, 2) -> %u\n", invert(32, 3, 2));
    return 0;
}


/*
    invert: return x with the n bits beginning at position p inverted
*/
unsigned invert(unsigned x, int p, int n)
{
    unsigned n_mask =  ~(~0 << n);
    int shift = p + 1 - n;
    return x ^ (n_mask << shift);
}