/* programe for Exercise 21
 * When either a tab or a single blank would suffice to reach a tab stop,
 * use tabstop
 * */
#include <stdio.h>

#define TABSTOP 4

int main()
{
    int c;          //charactor buffer
    int nb = 0;     //blank counter
    int nt = 0;     //tabstop counter
    int pos= 0;     //position in the line

    while ((c = getchar()) != EOF)
    {
        if (' ' == c)
        {
            if (((pos + 1) % TABSTOP) == 0)
            {    
                nt++;
                nb = 0;
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
            pos = 0;
        else 
            ++pos;
    }
}
