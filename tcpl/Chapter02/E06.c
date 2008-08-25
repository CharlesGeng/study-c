#include <stdio.h>

int setbits(int x, int p, int n, int y)
{
    return x & ~(~(~0 << n) << (p + 1 -n)) | 
        (y & ~(~0 << n))<< (p + 1 - n);
}

int main()
{
    int result = setbits (0x0F0, 4, 4, 0xF);
    printf ("%d\n", result);

    return 0;
}


