#include <stdio.h>

#define TABLENGTH   4   //tabspace length

int main()
{
    int c;
    int nb  = 0;    //blank count
    int pos = 0;    //current position

    while ((c = getchar()) != EOF)
    {
        if ('\t' == c)
        {
            nb  += TABLENGTH - pos % TABLENGTH;
            pos += nb;
        }
        else
        {
            //print the blank char
            while (nb > 0)
            {
                putchar(' ');
                --nb;
            }
            putchar(c);
            if ('\n' != c)
                ++pos;
            else
                pos = 0;
        }
    }
    return 0;
}
