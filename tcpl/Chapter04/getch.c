#include "calculator.h"

#define BUFSIZE 100

char buff[BUFSIZE];
int bufp = 0;
int ch;

int getch(void)
{
    return (bufp > 0) ? buff[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buff[bufp++] = c;
}

//get single character
int getsinglech(void)
{
    if (ch != 0)
    {
        int temp = ch;
        ch = 0;
        return temp;
    }
    else
    {
        return getchar();
    }
}

//unget single character
void ungetsinglech(int c)
{
    if (ch != 0)
        printf("ungetsinglech: too many characters\n");
    else
        ch = c;
}

void ungets(char *s)
{
}
