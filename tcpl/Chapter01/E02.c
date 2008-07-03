#include <stdio.h>

main()
{
    printf("Test \\c\n");
    //printf("\c");
    //this line will generate a warning:Unknown escape sequence
    printf("\n");
}
