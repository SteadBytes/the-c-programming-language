#include <stdio.h>

int bitcount(unsigned x);

int main(void)
{
    printf("bitcount(8) -> %u\n", bitcount(8));
    printf("bitcount(11) -> %u\n", bitcount(11));
    return 0;
}

/*
    bitcount: count 1 bits in x
    x &= (x-1) deletes rightmost bit in x:
        rightmost 1 bit of x will have a corresponding 0 bit in (x-1)
        i.e. 1001 &= (1001-1) = 1001 &= (1010) = 1000
    original bitcount always does n shifts, where n is the number of bits in x
    this bitcount will perform a number of ANDs equal to the number of set bits in x
*/
int bitcount(unsigned x)
{
    int b;
    for (b = 0; x != 0; x &= (x-1))
        if (x & 01)
            b++;
    return b;
}