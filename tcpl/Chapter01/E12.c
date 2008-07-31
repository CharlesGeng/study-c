#include <stdio.h>

#define INW     1
#define OUTW    0

int main()
{
    char c;
    int state = OUTW;
    while ((c = getchar()) != EOF)
    {
        if (c == '\t' || c == ' ' || c == '\n')
        {
            if (state == INW)
            {
                state = OUTW;
                putchar('\n');
            }
        }
        else if (state == OUTW)
        {    
            state = INW;
            putchar(c);
        }
        else
        {
            putchar(c);
        }
    }
    return 1;
}
