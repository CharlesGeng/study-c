#include "calculator.h"

#define BUFSIZE 100

char buff[BUFSIZE];
int bufp = 0;

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

void ungets(char *s)
{
}
