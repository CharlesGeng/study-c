#include <stdio.h>
#define SPACE ' '

int main()
{
    char c;
    int sp = 0;
    while((c = getchar()) != EOF)
    {
        if (c == SPACE)
        {
            if (sp == 0)
            {
                putchar(' ');
                sp = 1;
            }
            continue;
        }
        else
        {
            sp = 0;
        }
        putchar(c);
    }
}
