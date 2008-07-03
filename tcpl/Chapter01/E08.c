#include <stdio.h>

int main()
{
    char c = 0;
    int bCnt = 0, tCnt = 0, nCnt = 0;
    printf("Please Input, Exit(Ctrl-D)\n");
    while ((c = getchar()) != EOF)
    {
        if(' ' == c)
            ++bCnt;
        else if ('\t' == c)
            ++tCnt;
        else if ('\n' == c)
            ++nCnt;
    }
    printf("blank:%d tabstop:%d newline:%d\n", bCnt, tCnt, nCnt);
}
