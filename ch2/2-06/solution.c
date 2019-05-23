#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y);

int main(void)
{
    printf("setbits(32, 3, 2, 6) -> %u\n", setbits(32, 3, 2, 6));
    return 0;
}


/* setbits: return x with the n bits beginning at position p
    set to the rightmost n bits of y */
unsigned setbits(unsigned x, int p, int n, unsigned y)
{
    unsigned n_mask =  ~(~0 << n);
    int shift = p + 1 - n;
    // xx0000xx
    unsigned x_masked = x & ~(n_mask << shift);
    // 00yyyy00
    unsigned y_bits_shifted = (y & n_mask) << shift;
    // xxyyyyxx
    return x_masked | y_bits_shifted;
}