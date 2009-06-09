/*
 * Expend shorthand notations to equivalent complete list, for example: a-z --> abcdefgh...uvwxyz
 * current support:
 * 1. a-z 0-9 A-Z
 * 2. a-e-q
 * 3. -a-f-q
 * 4. a-f-q-
 * 5. a-f-q
 *
 * Unsupport:
 * 1.1-z
 * 2.A-z
 * 3.a-Z
 *
 * */
#include "GetLine.h"

#define LOW2HIGH    1
#define HIGH2LOW    2
#define EQUAL       3

int IsStrAvailable(int a, int b)
{
    if (a < b)
    {
        if (a >= 'a' && b <= 'z' ||
            a >= '0' && b <= '9' ||
            a >= 'A' && b <= 'Z')
            return LOW2HIGH;
    }
    else if (b < a)
    {
        if (b >= 'a' && a <= 'z' ||
            b >= '0' && a <= '9' ||
            b >= 'A' && a <= 'Z')
            return HIGH2LOW;
    }
    else if (a == b)
    {
        if (a >= 'a' && a <= 'z' ||
            a >= '0' && a <= '9' ||
            a >= 'A' && a <= 'Z')
            return EQUAL;
    }
    return 0;
}

void expandex (char *s1, char *s2)
{
    int i = 0;
    int j;
    while ( s1[i] != '\0')
    {
        //Expend '-'
        if ( s1[i] == '-' && i > 0 && s1[i+1] != '\0')
        {
            switch (IsStrAvailable(s1[i-1], s1[i+1]))
            {
                case LOW2HIGH:
                    for(j = s1[i-1] + 1; j < s1[i+1] ; ++j) 
                        *s2++ = j;
                    break;
                case HIGH2LOW:
                    for(j = s1[i-1] - 1; j > s1[i+1] ; --j) 
                        *s2++ = j;
                    break;
                case EQUAL:
                    *s2++ = s1[i-1];
                    ++i;
                    break;
                default:
                    *s2++ = s1[i];
            }
        }
        else
        {
            *s2++ = s1[i];
        }
        ++i;
    }
    *s2 = '\0';
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
