#include "GetLine.h"

int GetLine( char *str, int length)
{
    char *start = str;
    while (( str - start) < length && (*str = getchar()) != EOF && *str != '\n')
    {
        ++str;
    }
    *++str = '\0';
    if (*(str - 1) == EOF)
        return 0;
    return str - start;
}
