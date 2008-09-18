#include <stdio.h>
#include <string.h>

typedef struct
{
    int test;
    int outtest;
    char ctest[5];
}intstruct;

int dointstruct(intstruct *mytest, char *abc)
{
    mytest->test = 1234;
    printf("%d\n", mytest->test);

    strcpy((*mytest).ctest, "ABCD");
    printf("%s\n", mytest->ctest);

    strcpy(abc ,"testmyabc");
    printf("%s\n", abc);
}

int main()
{
    intstruct it;
    it.test = 4321;
    printf("%d\n", it.test);
    char c[2048];
    dointstruct(&it, c);
    printf("%s\n", c);
}

