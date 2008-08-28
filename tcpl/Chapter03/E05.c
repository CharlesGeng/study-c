#include <stdio.h>
#include <limits.h>
#include <string.h>

#define abs(x) ((x) >= 0 ? x : -x)

void itob(int n, char c[], int b)
{
    int i = 0;
    do
    {
        int t = abs(n % b); 
        c[i++] = (t <= 9) ? t + '0': t - 10 + 'A';
    }
    while((n/=b) != 0);

    c[i] = '\0';

    //print result;
    i = strlen(c);
    for (; i >= 0; --i)
        printf("%c", c[i]);
    printf("\n");
}

int main()
{
    char c[10];
    itob (0xFF, c, 17);
    return 0;
}
