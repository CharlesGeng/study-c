/*
 * =====================================================================================
 *
 *       Filename:  E11.c
 *
 *    Description:  Entab Detab
 *
 *        Version:  1.0
 *        Created:  2009年12月05日 18时08分45秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Neil Gunn (moomu), gengqi.cn@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include	<stdio.h>
#include	<stdlib.h>
#include	<ctype.h>
#include	<string.h>

#define MAXLENGTH 1000

int TABLENGTH = 4;

//Transform tabstops to space 
void detab(char *str, int tabLength)
{
    int index = 0;
    char temp[MAXLENGTH];
    char *start = str;
    while(*str != '\0')
    {
        if (*str == '\t')
        {
            int i = tabLength - index % tabLength;
            while (i--)
            {
                temp[index++] = ' ';
            }
        }
        else
        {
            temp[index++] = *str;
        }
        ++str;
    }
    strcpy(start, temp);
}

//Transform space to tabstops
void entab(char *str, int strLength, int tabLength)
{
    int flag = 0;
    char temp[strLength];
    int index = 0;
    while(flag < strLength)
    {
        if (str[flag] == ' ' && ((flag + 1) % tabLength == 0))
        {
            while(index > 0 && temp[index - 1] == ' ')
                --index;
            temp[index++] = '\t';
        }
        else
        {
            temp[index++] = str[flag];
        }
        ++flag;
    }
    temp[index] = '\0';
    strcpy(str, temp);
}

//get a string and return the length
int cgetline(char *str, int maxLength)
{
    char c;
    char *start = str;
    while ((c = getchar()) != '\0' && c != '\n' && c != EOF)
        *str++ = c;
    if (c == '\n')
        *str++ = '\n';
    *str = '\0';
    return str - start;
}

int main(int argc, char *argv[])
{
    while (--argc > 0 && (*++argv)[0] == '-')
    {
        char c;
        char string[MAXLENGTH];
        switch(c = *++argv[0])
        {
            case 'e':
            {
                int tablen = TABLENGTH;
                if (--argc > 0 && isdigit((*++argv)[0]))
                {
                    tablen = atoi(*argv);
                }
                int len = 0;
                while((len = cgetline(string, MAXLENGTH)) > 0)
                {
                    entab(string, len, tablen);
                    printf("%s", string);
                }
                break;
            }
            case 'd':
            {
                int tablen = TABLENGTH;
                if (--argc > 0 && isdigit((*++argv)[0]))
                {
                    tablen = atoi(*argv);
                }
                int length = 0;
                while((length = cgetline(string, MAXLENGTH)) > 0)
                {
                    detab(string, tablen);
                    printf("%s", string);
                }
                break;
            }
            default:
                printf("%s", "Unsupport parameter!\n");
                break;
        }
    }
    if (argc != 0)
    {
        printf("%s", "Parameters Error!\n");
    }
    return 0;
}

