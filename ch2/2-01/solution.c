#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(void)
{

    puts("Part a");
    puts("From limits.h/float.h:");
    printf("signed char: %d -> %d\n", SCHAR_MIN, SCHAR_MAX);
    printf("unsigned char: %d -> %d\n", 0, UCHAR_MAX);
    printf("char: %d -> %d\n", CHAR_MIN, CHAR_MAX);

    printf("signed short: %d -> %d\n", SHRT_MIN, SHRT_MAX);
    printf("unsigned short: %d -> %d\n", 0, USHRT_MAX);

    printf("signed int: %d -> %d\n", INT_MIN, INT_MAX);
    printf("unsigned int: %d -> %u\n", 0, UINT_MAX);

    printf("signed long: %ld -> %ld\n", LONG_MIN, LONG_MAX);
    printf("unsigned long: %d -> %lu\n", 0, ULONG_MAX);

    puts("\nFrom direct computation:");
    unsigned int i = ~0;
    printf("unsigned int: %d, %u\n", 0, i);
    printf("signed int: %d, %u\n", -(i / 2) - 1, i / 2);

    puts("Part b");
    puts("From limits.h/float.h:");
    printf("float: %f -> %f\n", FLT_MIN, FLT_MAX);
    printf("double: %f -> %f\n", DBL_MIN, DBL_MAX);
    printf("long double: %Lf -> %Lf\n", LDBL_MIN, LDBL_MAX);
    return 0;
}