#include "C05.h"

int main()
{
    int data = 0;
    while (getint(&data) != EOF)
        printf("you input: %d\n", data);
    return 0;
}

int getint(int *pi)
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

    for (*pi = 0; isdigit(c); c = getch())
        *pi = 10 * *pi + c - '0';
    *pi = sign * *pi;
    if (c != '\n' && c != EOF)
        ungetch(c);
    return c;
}
