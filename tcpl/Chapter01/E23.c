/*
 * CURRENT VERSION: 0.2
 * Created at:
 *      DATE: 2009-05-04
 *      Description:
 *          This Programe is Used to Remove the comments in the source files
 *
 * Modified at:
 *      Date: 2009-06-03 
 *      VERSION: 0.2
 *      LOG: 
 *          --BUG: Failure to deal with the code in this format: int a = 10; \/\*declare a integer\*\/
 *          --BUG: Failure to deal with the code in this format: char *str = "\/\*declare a integer\*\/"
 * */

#include <stdio.h>

#define MAXLINELENGTH 1000          //The Maximum Length Of A Line

int mygetline(char *str, int maxlength);
int RemoveComments(char *str, int length);

int main(int argc, char *argv[])
{
    char str[MAXLINELENGTH];
    int strLength = 0;
    while ((strLength = mygetline(str, MAXLINELENGTH)) > 0)
    {
        if( RemoveComments(str, strLength) > 0)
        {
            printf("%s", str);
        }
    }
    return 0;
}

//get string and return string's length
int mygetline(char str[], int maxlength)
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
        //Search "*/"
        if (flag && str[i] == '*' && i + 1 < length && str[i + 1] == '/')
        {
            char *j = str + i + 2;
            if (flag - 1 > 0)
                str += flag - 1;
            while (*str++ = *j++)
                ;
            flag = 0;
            return length - i;
        }
        else if (str[i] == '/' && i + 1 < length)
        {
            //deal quoted string
            if (i - 1 >= 0 && str[i - 1] == '"')
                continue;
            //Search "//"
            if (str[i + 1] == '/')
            {
                str[i++] = '\n';
                str[i]   = '\0';
                return i;
            }
            // Search "/*"
            else if (str[i + 1] == '*')
            {
                flag = i + 1;
                continue;
            }
        }
    }
    if (flag)
        return 0;
    return length;
}
