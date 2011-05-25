#include <stdio.h>

int mygetline(char str[]);
void copystr(char source[], char dest[]);

int main()
{
    char *longest;  //Longest String
    char *str;
    int max = 0;    //Longest String's Length
    int len = 0;

    while ((len = mygetline(str)) > 0)
    {
        if (len > max)
        {
            max = len;
            copystr(str, longest);
        }
    }
    if (max > 0)
    {
        printf("Max Length:%d\n", max);
        printf("%s", longest);
    }
    return 0;
}

// Get Str's Length
int mygetline(char str[])
{
    char c;
    int i = 0;
    while ((c = getchar()) != EOF && c != '\n')
    {
        str[i++] = c;
    }
    if (c == '\n')
    {
        str[i++] = c;
    }
    str[i] = '\0';
    return i;
}

//Copy string from Source to Dest
void copystr(char source[], char dest[])
{
    int i = 0;
    while ((dest[i] = source[i]) != '\0')
    {
        ++i;
    }
}
