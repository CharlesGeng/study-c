/*Convert Celsius to Fahrenheit
 * F = 9 * C / 5 + 32
 *2008-05-27
 *Write By nalegunn
 */

#include <stdio.h>

#define LOW     -30     //lowest Celsius
#define HIGH    40      //highest Celsius
#define STEP    2

//use for loop
void ConvertByForLoop()
{
    int   i = LOW;
    float f = 0.0;
    printf("%s", "Use For Loop\n");
    printf("%s", "Celsius\tFahrenheit\n");
    for (; i <= HIGH; i += STEP)
    {
        printf("%3d\t%6.2f\n", i, 9.0 * i / 5.0 + 32);
    }
    printf("%s", "***********************\n");
}

//use while loop
void ConvertByWhileLoop()
{
    int i = LOW;
    printf("%s", "Use While Loop\n");
    printf("%s", "Celsius\tFahrenheit\n");
    while (i <= HIGH)
    {
        printf("%3d\t%6.2f\n", i, 9.0 * i / 5.0 + 32);
        i += STEP;
    }
}

int main()
{
    ConvertByForLoop();
    ConvertByWhileLoop();
}


