/*
 * remove each character that match any character in des
 * */

#include <stdio.h>

#define MAXLENGTH 1000

void squeeze(char *, char *);
int GetLine(char *, int);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("ERROR: The Arguments Error!\n");
        return 0;
    }

    char src[MAXLENGTH];
    int count = 0;
    while ((count = GetLine(src, MAXLENGTH)) > 0)
    {
        squeeze(src, argv[1]);
        printf("%s", src);
    }
    return 0;
}

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

void squeeze(char *src, char *des)
{
    int i,j,k;
    i = k = 0;
    for (; src[i] != '\0'; ++i)
    {
        for (j = 0; des[j] != '\0' && src[i] != des[j]; ++j)
        {}
        if (des[j] == '\0')
        {
            src[k++] = src[i];
        }
    }
    src[k] = '\0';
}
