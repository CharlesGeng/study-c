#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLENGTH   100

char *itoa(int data, char *str)
{
    char *p;
    if (data / 10 == 0)
    {
        str[0] = data + '0';
        str[1] = '\0';
    }
    else
    {
        for ( p = itoa(data / 10, str); *p; p++);
        itoa(data % 10, p);
    }
    return str;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("USEAGE: E12 DATA\n");
        return;
    }

    int data = atoi(argv[1]);
    char ia[MAXLENGTH];
    printf("Input Data is: %d\n", data);
    itoa(data, ia);
    printf("The String is: %s\n", ia);
}
