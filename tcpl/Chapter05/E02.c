#include "C05.h"

int main()
{
    float data = 0.0;
    while (getfloat(&data) != EOF)
        printf("you input: %f\n", data);
    return 0;
}

int getfloat(float *pf)
{
    int c, sign;
    int temp;
    while (isspace(c = getch()))
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-')
    {
        ungetch(c);
        return 0;
    }

    sign = (c == '-') ? -1 : 1;
    temp = c;
    if (c == '-' || c == '+')
    {
        c = getch();
        if (!isdigit(c))
        {
            ungetch(c);
            ungetch(temp);
            return 0;
        }
    }

    for (*pf = 0.0; isdigit(c); c = getch())
        *pf = 10 * *pf + c - '0';
    if (c == '.')
    {
        c = getch();
        float t = 0.1;
        for (; isdigit(c); c = getch())
        {
            if (c > '0')
            {
                *pf = *pf + (c - '0') * t;
            }
            t /= 10.0;
        }
    }
    *pf = sign * *pf;
    if (c != '\n' && c != EOF)
        ungetch(c);
    return c;
}
