/*
 * Binary Search
 * */
#include <stdio.h>

int main()
{
    int test[] = {0, 1, 2, 3, 4, 5, 6, 7};
    int x = 11;
    int n = 9;
    int i = 0;

    for (i = 0;i < 0x2FFFFFF; ++i)
        binsearch(x, test, n);
    return 0;
}

int binsearch(int x, int v[], int n)
{
    int low = 0;
    int high = n - 1;
    int mid ;

    while (low < high)
    {
        mid = (high + low) / 2;
        if (x <= v[mid])
            high = mid;
        else
            low = mid + 1;
    }
    return x == v[low] ? low : -1;
}
