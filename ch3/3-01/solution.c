#include <stdio.h>

int binsearch(int x, int v[], int n);

int main(void)
{
    int x[5] = {2, 4, 6, 8, 10};
    printf("%d\n", binsearch(4, x, 5));
    return 0;
}

/*
    binsearch: find index of x in v[0] <= v[1] <= ... v[n-1] 
    return -1 if x not present
*/
int binsearch(int x, int v[], int n)
{
    int low = 0;
    int high = n - 1;
    int mid = (low + high) / 2;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (x <= v[mid])
        {
            high = mid;
        }
        else
        {
            low = mid + 1;
        }
    }
    return (x == v[low]) ? low : -1;
}