#include <stdio.h>

void lower(char str[])
{
    int i;
    for (i = 0; str[i] != '\0'; ++i)
    {
        str[i] = (str[i] >= 'A' && str[i] <= 'Z') ? str[i] - 'A' + 'a': str[i];
    }
}
int main()
{
    char test[] = "MyTest";
    lower(test);
    printf("%s\n", test);
    return 0;
}
