#include <stdio.h>

#define MAXWORDLENGTH 1000

int main()
{
    int counter[MAXWORDLENGTH];
    int i, wlength;
    wlength = 0;
    char c;
    for (i = 0; i < MAXWORDLENGTH; ++i)
    {
        counter[i] = 0;
    }

    //Count every word's length
    while ((c = getchar()) != EOF)
    {
        if (c == '\t' || c == '\n' || c == ' ')
        {
            if (wlength != 0 && wlength < MAXWORDLENGTH)
                ++counter[wlength];
            wlength = 0;
        }
        else
        {
            wlength ++;
        }
    }
    printf("\n");

}
