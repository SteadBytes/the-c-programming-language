#include <stdio.h>

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);
int is_leap(int year);

int main(void)
{
    int y = 2019;
    int m = 2;
    int d = 28;
    printf("day_of_year(%d, %d, %d) -> %d\n", y, m, d, day_of_year(y, m, d));

    int yd = 256;
    printf("month_day(%d, %d, &m, &d) -> ", y, yd);
    month_day(y, yd, &m, &d);
    printf("*m = %d, *d = %d\n", m, d);

    m = 0;
    d = 28;
    printf("day_of_year(%d, %d, %d) -> %d\n", y, m, d, day_of_year(y, m, d));

    m = 1;
    d = 32;
    printf("day_of_year(%d, %d, %d) -> %d\n", y, m, d, day_of_year(y, m, d));

    yd = 366;
    month_day(y, yd, &m, &d);
    printf("month_day(%d, %d, &m, &d) -> *m = %d, *d = %d\n", y, yd, m, d);
}

/* days per month daytab[0] = normal year, daytab[1] = leap year */
static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

/* day_of_year: return day of year from month and day */
int day_of_year(int year, int month, int day)
{
    if (month < 1 || month > 12)
    {
        printf("error: expected month to be 1 <= month <= 12, got %d\n", month);
        return -1;
    }
    int leap = is_leap(year);
    if (day < 1 || day > daytab[leap][month])
    {
        printf("error: expected day to be 1 <= day <= %d, got %d\n", daytab[leap][day], day);
        return -1;
    }
    char *p = daytab[leap];
    while (--month)
    {
        day += *++p;
    }
    return day;
}

/* month_day: set month, day from day of year. -1 if error */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int leap = is_leap(year);
    int max_days = leap ? 366 : 365;
    if (yearday < 1 || yearday > max_days)
    {
        printf("error: expected yearday to be 1 <= yearday <= %d, got %d\n", max_days, yearday);
        *pmonth = -1;
        *pday = -1;
        return;
    }
    char *p = daytab[leap];
    while (yearday > *++p)
    {
        yearday -= *p;
    }
    *pmonth = p - daytab[leap];
    *pday = yearday;
}

/* is_leap: return 1 if year is a leapyear else 0 */
int is_leap(int year)
{
    return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
}