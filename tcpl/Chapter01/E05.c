#include <stdio.h>

int main()
{
    float fahrenheit = 300.0;
    int step = 20;

    for (; fahrenheit >= 0.0; fahrenheit -= step)
    {
        printf("%4.1f\t%4.2f\n", fahrenheit, (5.0 / 9.0) * (fahrenheit - 32));
    }
    return 0;
}
