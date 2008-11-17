#include <stdio.h>
#include <ctype.h>

#define MAXLINE     1000
#define ERRORVAL    -1

double atof(char cdata[])
{
    double result = 0.0, power = 1.0;
    int i = 0;
    int sign = 1;
    char esign = '+';
    //find first non blank character
    while (isspace(cdata[i]))
        ++i;

    //check it's parity
    if (cdata[i] == '-')
    {        
        sign = -1;
        ++i;
    }

    //Get the Integer part value
    for (; cdata[i] >= '0' && cdata[i] <= '9'; ++i)
    {
        result = result * 10 + cdata[i] - '0';
    }

    if (cdata[i] == '.')
    {
        ++i;
    }

    //Get the Decimal part
    for (; cdata[i] >= '0' && cdata[i] <= '9'; ++i)
    {
        result = result * 10 + cdata[i] - '0';
        power *= 10;
    }

    if (cdata[i] == 'e' || cdata[i] == 'E')
    {
        esign = cdata[++i];
        ++i;
    }

    int t = 0, j = 0;
    for (; cdata[i] >= '0' && cdata[i] <= '9'; ++i)
    {
        t = t * 10 + cdata[i] - '0';
    }

    if (esign == '-')
    {    
        for (; j < t; ++j)
            power *= 10;
    }
    else
    {
        for (; j < t; ++j)
            power /= 10;
    }

    return result / power;
}

int main()
{
    char test[MAXLINE];
    scanf("%s", test);
    double temp = atof(test);
    printf("%f\n",temp);
    return 0;
}
