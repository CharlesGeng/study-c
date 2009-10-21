#include "C05.h"

#define MAX_STRING_LENGTH   1000

static char string[MAX_STRING_LENGTH];

int getline(char *str);

/*atoi();
itoa();
reverse();
strindex();
getop();*/

int main()
{
    printf("Test the function GetLine\n");
    while (getline(string) > 0)
    {
        printf("%s\n", string);
    }
    return 0;
}

//get a line, return the length
int getline(char *str)
{
    char *temp = str;
    while ((*str = getchar()) != '\0' && *str != '\n' && *str != EOF)
    {
        ++str;
    }
    if (*str != '\0')
        *++str = '\0';
    return str - temp - 1;
}
