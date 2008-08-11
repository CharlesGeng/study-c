#include <stdio.h>

#define MAXLINE     1000

const int TABLEN = 8;
int getline(char str[]);
void outputline(char str[]);

int main()
{
    char str[MAXLINE];
    while (getline(str) > 0)
    {
        outputline(str);
    }
    return 0;
}

int getline(char str[])
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

        }
        else
        {
            putchar(str[i]);
            ++column;
        }
    }
}
