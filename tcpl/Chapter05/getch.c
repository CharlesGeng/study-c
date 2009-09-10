#include "C05.h"

#define LENGTH 1000

static int index = 0;
static int array[LENGTH];

int getch()
{
    return (index > 0) ? array[index--] : getchar();
}

void ungetch(int c)
{
    if (index < LENGTH)
        array[index++] = c;
    else
        printf("ERROR: The buffer is empty!");
}
