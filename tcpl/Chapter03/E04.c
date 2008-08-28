#include <stdio.h>
#include <limits.h>
#include <string.h>

void itoa(int n, char c[])
{
    int i = 0;
    int sign = n;
    if (n < 0)
    {
        do
        {
            c[i++] = -(n % 10) + '0';
        }
        while((n/=10) < 0);
    }
    else 
    {
        do
        {
            c[i++] = n % 10 + '0';
        }
        while((n/=10) > 0);
    }
    if (sign < 0)
        c[i++] = '-';
    c[i] = '\0';

    //print result;
    i = strlen(c);
    for (; i >= 0; --i)
        printf("%c", c[i]);
    printf("\n");
}

int main()
{
    int n = INT_MIN ;
    printf ("%d\n", n);
    char c[SHRT_MAX];
    itoa(n, c);

    n = INT_MAX;
    printf ("%d\n", n);
    itoa(n, c);
    return 0;
}
