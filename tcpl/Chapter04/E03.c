#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "opval.h"
#include "getch.h"

#define MAXOP   100
#define NUMBER  '0'

int getop(char s[])
{
    int i,c;

    while ((s[0] = c = getch()) == ' '|| c == '\t')
        ;

    s[1]='\0';
    if (!isdigit(c) && c != '.')
        return c;
    i=0;
    if (isdigit(c))
        while (isdigit(s[++i]=c=getch()))
            ;
    if (c=='.')
        while (isdigit(s[++i]=c=getch()))
            ;
    s[i]='\0';
    if (c!=EOF)
        ungetch(c);
    return NUMBER;
}

int main()
{
    int type;
    double op2;
    char s[MAXOP];
    getop(s);

    while ((type = getop(s)) != EOF) 
    {
        switch(type) {
            case NUMBER:
                push(atof(s));
            case '+':
                push(pop()+pop());
            case '*':
                push(pop()*pop());
            case '-':
                op2=pop();
                push(pop()-op2);
                break;
            case '/':
                op2=pop();
                if(op2!=0.0)
                    push(pop()/op2);
                else
                    printf("error:zero divisor\n");
                break;
            case '\n':
                printf("\t%.8g\n",pop());
                break;
            default:
                printf("error:unknown command %s\n",s);
                break;
        }
    }
    return 0;
}


