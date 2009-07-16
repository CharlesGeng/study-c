#include <stdio.h>

//reverse a string
void reverse(char *s)
{
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {       
        printf("Error: No input string!\n");
        return 0;
    }

    printf("%s\n", argv[1]);
    reverse(argv[1]);
    printf("%s\n", argv[1]);
}
