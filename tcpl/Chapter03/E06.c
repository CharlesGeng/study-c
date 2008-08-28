#include <stdio.h>
#include <limits.h>
#include <string.h>

void itoa(int n, char c[], int minlen)
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
    //Add blanks 
    for (;i < minlen; ++i)
        c[i] = ' ';
    c[i] = '\0';

    //print result;
    i = strlen(c);
    for (; i >= 0; --i)
        printf("%c", c[i]);
    printf("\n");
}

int main()
{
    int n = 10;
    printf ("%d\n", n);
    char c[SHRT_MAX];
    itoa(n, c, 8);

    n = 123456789;
    printf ("%d\n", n);
    itoa(n, c, 8);
    return 0;
}
