#include <stdio.h>

#define MAXWORD 1000

int main()
{
    int counter[MAXWORD];
    int i, wlength;
    wlength = 0;
    char c;
    for (i = 0; i < MAXWORD; ++i)
    {
        counter[i] = 0;
    }

    //Count every word's length
    i = 0;
    while ((c = getchar()) != EOF)
    {
        if (c == '\t' || c == '\n' || c == ' ')
        {
            if (wlength != 0 && wlength < MAXWORD)
                counter[++i] = wlength;
            wlength = 0;
        }
        else
        {
            ++wlength;
        }
    }
    printf("\n");

    //horizontal histogram
    for (i = 0; i < MAXWORD; ++i)
    {
        int j;
        if (counter[i] > 0)
        {
            printf ("%d", i);
            for (j = 0; j < counter[i]; ++j)
            {
                printf("*");
            }
            printf("\n");
        }
    }

    //vertical histogram
    /*for (i = 0; i < MAXWORD; ++i)
    {
        if (counter[i] != 0)
            printf ("%d", i);
    }
    printf("\n");*/


}
