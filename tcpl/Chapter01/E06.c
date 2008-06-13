#include <stdio.h>

int main()
{
    printf("The value of EOF is %d\n", EOF);

    char c;
    if((c = getchar()) != EOF)
    {
        printf ("Char is %c, expression value is %d\n", c, 1);
    }
    else
    {
        printf ("Char is %c, expression value is %d\n", c, 0);
    }
}
