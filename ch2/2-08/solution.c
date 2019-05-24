#include <stdio.h>
#include <limits.h>

unsigned rightrot(unsigned x, int n);

int main(void)
{
    printf("rightrot(8, 2) -> %u\n", rightrot(8, 2));
    printf("rightrot(11, 2) -> %u\n", rightrot(11, 2));
    printf("rightrot(8, 8) -> %u\n", rightrot(8, 8));
    return 0;
}

/*
    rightrot: return x rotated to the right by n bit positions
    rightrot(8, 2) -> rightrot(0100, 2) -> 0010 -> 2
    rightrot(11, 2) -> rightrot(1011, 2) -> 1110 -> 14 
*/
unsigned rightrot(unsigned x, int n)
{
    int n_rot = n % CHAR_BIT;
    // rotation by number of bits in x -> no effect
    if (n_rot == 0)
        return x;

    // rightmost n bits
    unsigned r_bits = x & ~(~0 << n_rot);
    // rightmost n bits shifted to leftmost position
    unsigned r_bits_l_shifted = r_bits << CHAR_BIT - n_rot;
    return (x >> n_rot) | r_bits_l_shifted;
}