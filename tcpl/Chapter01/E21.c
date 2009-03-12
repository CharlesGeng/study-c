#include <stdio.h>

#define TABSTOP 4

int main()
{
    int c;
    int nb, nt, pos;

    nb = nt = 0;
    pos = 1;

    while ((c = getchar()) != EOF)
    {
        if ( c == ' ')
        {
            if ((pos % TABSTOP) == 0)
            {    
                if (nb == 0)
                {    
                    nb++;
                }
                else
                {
                    nt++;
                    if (nb > TABSTOP)
                        nb -= TABSTOP;
                    else
                        nb = 0;
                }
            }
            else
            {
                nb++;
            }
        }
        else
        {
            while (nt > 0)
            {
                putchar('\t');
                --nt;
            }
            while (nb > 0)
            {
                putchar(' ');
                --nb;
            }
            putchar(c);
        }
        if (c == '\n')
            pos = 1;
        else 
            ++pos;
    }
}
