/*
 * VERSION: 0.1
 * DATE:    2009-05-04
 * Description:
 *          This Programe is Used to Remove the comments in the source files
 * */
#include <stdio.h>

#define MAXLINELENGTH 1000          //The Maximum Length Of A Line

int getline(char *str, int maxlength);
int RemoveComments(char *str, int length);

int main(int argc, char *argv[])
{
    char str[MAXLINELENGTH];
    int strLength = 0;
    while ((strLength = getline(str, MAXLINELENGTH)) > 0)
    {
        if( RemoveComments(str, strLength) > 0)
        {
            printf("%s", str);
        }
    }
    return 0;
}

//get string and return string's length
int getline(char str[], int maxlength)
{
    int i;
    int c = 0;
    for ( i = 0; i < maxlength - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
    {
        str[i] = c;
    }

    if (c == '\n')
    {
        str[i++] = '\n';
    }
    str[i] = '\0';

    return i;
}

int RemoveComments(char *str, int length)
{
    int i = 0;
    static int flag = 0;

    for (i = 0; i < length; ++i)
    {
        //END of Multiple Comments Line
        if (str[i] == '*' && i + 1 < length && str[i + 1] == '/')
        {
            flag = 0;
            char *j = str + i + 2;
            while (*str++ = *j++)
                ;
            return length - i;
        }
        else if (str[i] == '/' && i + 1 < length)
        {
            if (str[i + 1] == '/')
            {
                str[i++] = '\n';
                str[i]   = '\0';
                return i;
            }
            else if (str[i + 1] == '*')
            {
                flag = 1;
                continue;
            }
        }
    }
    if (flag)
        return 0;
    return length;
}
