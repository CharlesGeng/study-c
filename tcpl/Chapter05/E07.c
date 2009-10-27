#include <stdio.h>

#define     ARRAY_MAX_LENGTH    100
#define     MAX_LINES           30

int mygetline(char *str, int length);
int myreadlines(char *linePtr[], char *strs, int maxLines, int strsLength);

int main()
{
    char mem[ARRAY_MAX_LENGTH];
    char *linePointer[MAX_LINES];
    int lines = myreadlines(linePointer, mem, MAX_LINES, ARRAY_MAX_LENGTH);
    int i;
    for (i = 0; i < lines; ++i)
        printf("%s", linePointer[i]);
    return 0;
}

int mygetline(char *str, int length)
{
    char *end = str + length;
    while (str < end && (*str = getchar()) != '\n' && *str != EOF)
    {
        ++str;
    }

    if (*str == '\n')
        ++str;
    *str = '\0';
    return str + length - end;
}

int myreadlines(char *linePtr[], char *strs, int maxLines, int strsLength)
{
    int i;
    char *end = strs + strsLength;
    for (i = 0; i < maxLines && end > strs; ++i)
    {
        int len = mygetline(strs, end - strs); 
        if(len > 0)
        {
            linePtr[i] = strs;
            strs += len + 1;
        }
        else
        {
            break;
        }
    }
    return i;
}
