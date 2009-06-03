#include "GetLine.h"

int any(char src[], char des[]);

int main()
{
    char src[] = "azaqabcdefgh";
    char des[] = "fq";
    printf("%d\n", any(src, des));
    return 0;
}


int any(char src[], char des[])
{
    int i,j;
    for (i = 0; src[i] != '\0'; ++i)
    {
        for (j = 0; des[j] != '\0' && src[i] != des[j]; ++j)
        {}
        if (des[j] != '\0')
        {
            return i;
        }
    }
    return -1;
}
