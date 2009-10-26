#include "C05.h"

#define MAX_STRING_LENGTH   1000

static char string[MAX_STRING_LENGTH];

int GetLine(char *str, int length);

/*atoi();
itoa();
reverse();
strindex();
getop();*/

int main()
{
    //Test GetLine Function
    while (GetLine(string, MAX_STRING_LENGTH) > 0)
    {
        printf("%s", string);
    }
    return 0;
}

//get a line, return the length
int GetLine(char *str, int length)
{
    char *temp = str;
    while (length-- > 0 && (*str = getchar()) != '\n' && *str != EOF)
    {
        ++str;
    }

    if (*str == '\n')
        *++str = '\0';
    else
        *str = '\0';
    return str - temp;
}
