/*
 * this programe is used to set bits, it will return x with the n bits that begin at p set to the rightmost n bits
 * of y
 * */
#include <stdio.h>

int setbits(int x, int p, int n, int y)
{
    return x & ~((~0 << p) ^ (~0 << (p + n))) |
        ((y & ~(~0 << n )) << p);
}

int main()
{
    int result = setbits (0x000, 0, 3, 0x0);
    printf ("setbits:%d\n", result);
    return 0;
}


