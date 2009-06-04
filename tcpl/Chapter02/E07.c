/*
 * Use ^ to invert number
 * */
#include <stdio.h>

int invert(int x, int p, int n)
{
    return x & ~((~(~0 << n)) << (p + 1 -n)) |
        (~x >> (p + 1 -n) & ~(~0 << n)) << (p + 1 -n);
}

//2009-06-04 added
int invertEX(int x, int p, int n)
{
    return x ^ (~(~0U << n) << p);
}

//print the integer in hex
void printbinary(int x)
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
    int test = 0x123456;
    int result = invert(test, 6, 4);
    printbinary(test);
    printbinary(result);
    return 0;
}
