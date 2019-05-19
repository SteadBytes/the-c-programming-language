#include <stdio.h>

/* print Fahrenheit-Celsius table for 0 20, ..., 300; Fahrenheit */

int fahr_to_celsius(float fahr);

int main(void)
{
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    fahr = lower;
    printf("%3s %6s\n", "F", "C");
    while (fahr <= upper)
    {
        celsius = fahr_to_celsius(fahr);
        printf("%3.0f %6.1f\n", fahr, celsius);
        fahr = fahr + step;
    }

    return 0;
}

int fahr_to_celsius(float fahr)
{
    return (5.0 / 9.0) * (fahr - 32.0);
}