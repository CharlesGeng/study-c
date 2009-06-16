#include "calculator.h"

void showinf(char *str)
{
    printf("%s\n", str);
}

int main()
{
    char str[MAXLENGTH];
    int c = 0;
    int i = 0;

    while ((c = getchar()) != EOF)
    {
        if (c == '\n')
        {
            showinf("******Show top element******");
            showtop();
            showinf("******Swap top element******");
            swaptop();
            showinf("******Show top element******");
            showtop();
            duplicatetop();
            clear();
        }
        //blank charactor, push it
        else if (c == ' ' || c == '\t')
        {
            str[i] = '\0';
            push(atof(str));
            i = 0;
        }
        else
        {
            str[i++] = c;
        }
    }
    return 0;
}
