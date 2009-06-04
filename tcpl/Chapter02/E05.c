#include "GetLine.h"

int any(char src[], char des[]);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("%s\n", "ERROR: Arguments error!");
        return;
    }

    char str[MAXLENGTH];
    while (GetLine(str, MAXLENGTH) > 0)
    {
        printf("%d\n", any(str, argv[1]));
    }
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
