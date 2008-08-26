#include <stdio.h>

int bitcount(unsigned int x)
{
    int i = 0;
    for (; x != 0; x &= (x - 1))
        i ++;
    return i;
}

int main()
{
    int result = 0;
    int test1 = 0xF;
    int test2 = 0xFF;
    result = bitcount (test1);
    printf("%d\n", result);
    result = bitcount (test2);
    printf("%d\n", result);
    return 0;
}
