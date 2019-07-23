#include <stdio.h>

/*
    isupper_time_save: non-zero if c is upper case, 0 if not
    optimised to save time by avoiding the overhead of a function call
*/
#define isupper_time_save(c) ((c >= 'A' && c <= 'Z'))

int isupper_space_save(char c);

int main(void)
{
    printf("isupper_space_save('a') -> %d\n", isupper_space_save('a'));
    printf("isupper_space_save('A') -> %d\n", isupper_space_save('A'));
    printf("isupper_space_save('z') -> %d\n", isupper_space_save('z'));
    printf("isupper_space_save('Z') -> %d\n", isupper_space_save('Z'));

    printf("isupper_time_save('a') -> %d\n", isupper_time_save('a'));
    printf("isupper_time_save('A') -> %d\n", isupper_time_save('A'));
    printf("isupper_time_save('z') -> %d\n", isupper_time_save('z'));
    printf("isupper_time_save('Z') -> %d\n", isupper_time_save('Z'));
}

/*
    isupper_space_save: non-zero if c is upper case, 0 if not
    optimised to save space by isolating code within a function
*/
int isupper_space_save(char c)
{
    return (c >= 'A' && c <= 'Z');
}