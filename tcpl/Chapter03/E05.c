#include <stdio.h>
#include <limits.h>
#include <string.h>

#define abs(x) ((x) >= 0 ? x : -x)

void itob(int n, char *c, int b)
{
    int i = 0;
    printf("SRC: %d\n", n);
    do
    {
        int t = abs(n % b); 
        c[i++] = (t <= 9) ? t + '0': t - 10 + 'A';
    }
    while((n/=b) != 0);

    c[i] = '\0';

    //print result;
    printf("DES: ");
    i = strlen(c);
    for (; i >= 0; --i)
        putchar(c[i]);
    putchar('\n');
}

int atoi (char *str)
{
    int result = 0;
    while (*str != '\0')
    {
        if (*str >= '0' && *str <= '9')
            result = result * 10 + (*str - '0');
        ++str;
    }
    return result;
}

int main(int argc, char *argv[])
{
    char c[100];
    if (argc != 3)
    {
        printf("%s\n", "USEAGE: E05 value base");
        return 0;
    }
    itob (atoi(argv[1]), c, atoi(argv[2]));
    return 0;
}
