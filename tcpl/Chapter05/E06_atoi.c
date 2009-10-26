#include <stdio.h>
#include <strings.h>
#include <limits.h>
#include <ctype.h>

static int atoi(char *str);
static char *itoa(int num,char *str,int radix);

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
    char strdata[64];
    itoa(data, strdata, 10);
    printf("%s\n", strdata);
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
        if ((temp = temp * 10 + (*str - '0')) < INT_MAX )
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

//integer to string
char *itoa(int num,char *str,int radix)
{
    char table[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *start = str;
    int negative = 0;

    //0
    if (num == 0)
    {
        *str++ = '0';
        *str = '\0';
        return start ;
    }
    //negative
    else if (num < 0)
    {
        *str++ = '-';
        ++start;
        num *= -1;
        negative = 1;
    }
    //convert number
    while (num)
    {
        *str++ = table[num % radix];
        num /= radix;
    }
    *str = '\0';
    //revert number
    while((str - start) / 2 > 0)
    {
        char temp = *--str;
        *str = *start;
        *start = temp;
        ++start;
    }
    if (negative)
        --str;
    return str;
}
