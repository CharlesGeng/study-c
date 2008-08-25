#include <stdio.h>

unsigned int rightrot (unsigned int x, int n)
{
    return x >> n |
    (x & ~(~0 << n)) << (sizeof(unsigned int) * 8) - n;
}

//print the integer in hex
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
