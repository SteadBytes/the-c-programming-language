#include <stdio.h>

/*
    swap: interchange arguments x and y of type t
    N.B tmp must not be used as an argument name
*/
#define swap(t, x, y) \
    {                 \
        t tmp = y;    \
        y = x;        \
        x = tmp;      \
    }

int main(void)
{
    int x = 1;
    int y = 2;
    printf("Before swap: x=%d, y=%d\n", x, y);
    swap(int, x, y);
    printf("After swap: x=%d, y=%d\n", x, y);
}