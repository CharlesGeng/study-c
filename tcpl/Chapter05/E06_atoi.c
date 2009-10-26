#include <stdio.h>
#include <strings.h>
#include <limits.h>
#include <ctype.h>

static int atoi(char *str);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("NOTE: E06_atoi is a program test int convertor\n");
        printf("USAGE: E06_atoi [signed integer]!\n");
        return -1;
    }
    int data = atoi(argv[1]);
    printf("input number is: %d\n", data);
    return 0;
}

int atoi(char *str)
{
    long long temp   = 0;
    int data    = 0;
    int sign    = 1;
    while (!isdigit(*str))
    {
        if (*str == '-')
            sign = -1;
        ++str;
    }

    while (isdigit(*str))
    {
        if ((temp = temp * 10 + (*str - '0')) < INT_MAX && ((temp & 0x80000000) == 0))
            data = (int)temp;
        else
        {
            printf("ERROR: you input number is overload to integer!\n");
            return 0;
        }
        ++str;
    }
    data *= sign;
    return data;
}

