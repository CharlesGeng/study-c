#include <stdio.h>

int main()
{
    int test[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int x = 21;
    int n = 8;
    printf("%d\n", binsearch(x, test, n));
    return 0;
}

int binsearch(int x, int v[], int n)
{
    int low = 0;
    int high = n - 1;
    int mid = (high + low) / 2;

    while(low < high && x != v[mid])
    {
        if (x < v[mid])
            high = mid - 1;
        else
            low = mid + 1;
        mid = (high + low) / 2;
    }
    if (x == v[mid])
        return mid;
    else 
        return -1;
}
