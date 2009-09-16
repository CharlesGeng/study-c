#include <stdio.h>

void mystrcat(char *dst, char *src);

int main()
{
    char s1[1000] = "string1";
    char *s2 = "string2";
    mystrcat(s1, s2);
    printf("%s\n", s1);
    return 0;
}

//copy *src to the tail of *dst
void mystrcat(char *dst, char *src)
{
    while(*dst++ != '\0')
        ;
    dst--;
    while(*dst++ = *src++)
        ;
}
