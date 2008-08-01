#include <stdio.h>

#define MAXWORD 10

extern void PrintHistogramHorizontal(int counter[]);
extern void PrintHistogramVertical(int counter[]);

int main()
{
    int counter[MAXWORD];
    int i, wlength, maxlength;
    wlength = maxlength = 0;
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
                counter[i++] = wlength;
            wlength = 0;
        }
        else
        {
            ++wlength;
        }
    }
    printf("\n");

    PrintHistogramHorizontal(counter);
    PrintHistogramVertical(counter);
}

//horizontal histogram
void PrintHistogramHorizontal(int counter[])
{
    int i;
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
    printf("\n");


}

//vertical histogram style
void PrintHistogramVertical(int counter[])
{
    int i, maxlength;
    maxlength = 0;
    //Get the longest word length
    for (i = 0; i < MAXWORD; ++i)
    {
        if (maxlength < counter[i])
            maxlength = counter[i];
    }

    for (i = maxlength; i > 0; --i)
    {
        int j;
        for (j = 0; j < MAXWORD; ++j)
        {
            if (counter[j] < i)
            {
                printf ("  ");
            }
            else
            {
                printf ("* ");
            }
        }
        printf("\n");
    }
    printf("\n");
}
