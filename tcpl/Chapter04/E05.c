/*
 * calculator just for sin, exp and power
 *
 * */

#include "calculator.h"

#define NUMBER      '0'     //number
#define FUNCTION    '1'     //for sin exp power

void DealFunction(char *s);
int getop(char *s);

int main()
{
    int result = 0;
    char s[MAXLENGTH];

    while ((result = getop(s)) != EOF)
    {
        switch(result)
        {
            case NUMBER:
                push(atof(s));
                break;
            case FUNCTION:
                DealFunction(s);
                break;
            case '+':
            case '-':
            case '*':
            case '/':
                printf("Not support now!\n");
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                break;
        }
    }
}

//Get Operator
int getop(char *s)
{
    int c = 0;
    int i = 0;

    s[i] = '\0';

    //over blank charactor
    while ((s[i] = c = getch()) == ' ' || c == '\t')
        ;

    //Get Number
    while(isdigit(c = getch()))
    {
        s[i++] = c;
    }

    if (c == '.')
    {
        s[i++] = '.';
        //unsupport float: 123.123e-2
        while(isdigit(c = getch()))
        {
            s[i++] = c;
        }
    }
    if (i > 1)
    {
        s[i] = '\0';
        ungetch(c);
        return NUMBER;
    }
    return c;
}

void DealFunction(char *s)
{
/*    char *fn = tolower(s);
    double temp = 0.0;
    switch (fn)
    {
        case "sin":
            push(sin(pop()));
            break;
        case "cos":
            push(cos(pop()));
            break;
        case "exp":
            push(exp(pop()));
            break;
        case "pow":
            temp = pop();
            push(pow(pop(), temp));
            break;
        default:
            printf("Unsupport function!");
            break;
    }*/
}

