#include <stdio.h>

void squeeze(char src[], char des[]);

int main()
{
    char src[] = "azaqabcdefgh";
    char des[] = "abcd";
    squeeze(src, des);
    printf("%s\n", src);
    return 0;
}


void squeeze(char src[], char des[])
{
    int i,j,k;
    i = k = 0;
    for (; src[i] != '\0'; ++i)
    {
        for (j = 0; des[j] != '\0' && src[i] != des[j]; ++j)
        {}
        if (des[j] == '\0')
        {
            src[k++] = src[i];
        }
    }
    src[k] = '\0';
}
