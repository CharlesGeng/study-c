#include <stdio.h>

#define MIN_MONTH   1
#define MAX_MONTH   12

#define MIN_DAY     1

#define LEAP_DAYS   366     //all days of leap year
#define UNLEAP_DAYS 365     //all days of none leap year

int day_of_year(int year, int month, int day);
void month_day(int year, int day, int *pmonth, int *pday);

static int daytable[2][13] = {{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

int main()
{
    int year, month, day;
    for (year = 2000, month = 1, day = 1; year < 2009; ++year, ++month, ++day)
    {
        printf("year: %d\tmonth: %d\tday: %d\n", year, month, day);
        int doy = day_of_year(year, month, day);
        if (doy > 0)
        {
            printf("day of year: %d\n", doy);
        }

        int *pm = &month;
        int *pd = &day;
        month_day(year, doy, pm, pd);
        printf("month: %d\tday: %d\n", *pm, *pd);
    }
    return 0;
}

int day_of_year(int year, int month, int day)
{
    //check param 'month'
    if (month < MIN_MONTH || month > MAX_MONTH)
        return -1;

    int i = 0;
    int leap = (year%4 == 0 && year%100 != 0) || (year%400 == 0);
    int *dt = &daytable[leap][1];

    //check param 'month'
    if (day < MIN_DAY || month > daytable[leap][month])
        return -2;

    for (i = 1; i < month; ++ i)
    {
        day += *dt++;
    }
    return day;
}

void month_day(int year, int day, int *pmonth, int *pday)
{
    int leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    int i = 1;

    if ((leap && day >= LEAP_DAYS) || day >= UNLEAP_DAYS)
        return;

    int *dt = &daytable[leap][1];
    for (; day > *dt; ++i)
    {
        day -= *dt++;
    }

    *pmonth = i;
    *pday = day;
}
