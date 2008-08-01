#include <stdio.h>

#define ALPHACOUNT 26

int main()
{
    int counter[ALPHACOUNT];
    int i;
    char c;
    // set array's every item zero;
    for (i = 0; i < ALPHACOUNT; ++i)
    {
        counter[i] = 0;
    }

    while ((c = getchar()) != EOF)
    {
        if (c >= 'a' && c <= 'z')
        {
            ++ counter[c - 'a'];
        }
        else if (c >= 'A' && c <= 'Z')
        {
            ++ counter[c - 'A'];
        }
        continue;
    }

    for (i = 0; i < ALPHACOUNT; ++i)
    {
        printf("%d ", counter[i]);
    }
    printf("\n");
    for (i = 0; i < ALPHACOUNT; ++i)
    {
        printf("%c ", i + 'a');
    }
    printf("\n");
}
