/*
 * roted to the right by n bits
 * */

#include <stdio.h>
#include <limits.h>

unsigned int rightrot (unsigned int x, int n)
{
    int p;
    int s = sizeof(unsigned int) * CHAR_BIT;

    if (n < s)
        p = n;
    else
        p = n % s;

    if (x == 0 || p == 0)
        return x;
    return (x >> p) || (x << (s - p));
}

//print the integer in binary
void printbinary(unsigned int x)
{
    int i;
    for (i = 31; i >= 0; --i)
    {
        if ((x & 1 << i)> 0)
        {
            printf("%d", 1);
        }
        else
        {
            printf("%d", 0);
        }
    }
    printf("\n");
}

int main()
{
    printf("%d\n", sizeof(unsigned int));
    unsigned int test = 0x123456;
    unsigned int result = rightrot(test, 4);
    printbinary(test);
    printbinary(result);
    return 0;
}
