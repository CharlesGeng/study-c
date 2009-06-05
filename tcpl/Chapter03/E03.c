/*
 * Expend shorthand notations to equivalent complete list, for example: a-z --> abcdefgh...uvwxyz
 * current support:
 * 1. a-z 0-9 A-Z
 * 2. a-e-q
 * 3. -a-f-q
 * 4. a-f-q-
 * 5. a-f-q
 *
 * */

#include "GetLine.h"

void expandex (char *s1, char *s2)
{
    char *start = s1;
    while ( *s1 != '\0')
    {
        if ( *s1 == '-' && (s1 - start) > 0)
        {
        }
        else
        {
        }
    }
}

int main()
{
    char dest[MAXLENGTH];
    char src[MAXLENGTH];
    while (GetLine(src, MAXLENGTH) > 0)
    {
        expandex(src, dest);
        printf("SRC: %s\n", src);
        printf("DET: %s\n", dest);
    }
    return 0;
}
