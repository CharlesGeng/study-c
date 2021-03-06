#include <stdio.h>

#define MAXLINE     1000

const int TABLEN = 8;
int mygetline(char str[]);
void outputline(char str[]);

int main()
{
    char str[MAXLINE];
    while (mygetline(str) > 0)
    {
        outputline(str);
    }
    return 0;
}

int mygetline(char str[])
{
    char c;
    int i = 0;
    while ((c = getchar()) != EOF && c != '\n')
    {
        str[i++] = c;
    }
    if (c == '\n')
        str[i++] = c;
    str[i] = '\0';
    return i;
}

void outputline(char str[])
{
    int i = 0;
    int column = 0;
    for (; str[i] != '\0'; ++i)
    {
        if (str[i] == '\t')
        {
            int j = 0;
            int len = TABLEN - column % TABLEN;
            for (; j < len; ++j)
                putchar(' ');
            column += len;
        }
        else
        {
            putchar(str[i]);
            ++column;
        }
    }
}
