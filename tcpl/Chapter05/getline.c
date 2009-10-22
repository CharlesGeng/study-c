#include <stdio.h>

#define MAX_STRING_LENGTH   1000

static char string[MAX_STRING_LENGTH];
int GetLine(char *str, int MaxLength);

int main()
{
    while(GetLine(string, MAX_STRING_LENGTH) > 0)
        ;
    return 0;
}

int GetLine(char *str, int MaxLength)
{
    int i = 0;
    int c;
    while (MaxLength-- > 0 && (c = getchar()) != '\n' && c != EOF)
    {
        str[i++] = c;
    }
    if (c == '\n')
        str[i++] = '\n';
    str[i] = '\0';
    return i;
}
