/*
 * getsinglech & ungetsinglech
 *
 * */

#include "calculator.h"

int main()
{
    int c = getsinglech();
    printf("get a char from console: %c\n", c);
    ungetsinglech(c);
    printf("unget a char: %c\n", c);
    return 0;
}
