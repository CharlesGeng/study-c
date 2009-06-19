#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLENGTH   100

char *myitoa(int data)
{
    char *s;
    return s;
}

int main()
{
    int i = 0;
    for (i = 0; i < 10; ++i)
    {
        srand((int)time(0));
        int data = rand();
        printf("Data: %d\n", data);
        sleep(1);
        printf("String: %s\n", myitoa(data));
    }
}
