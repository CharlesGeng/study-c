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
    return 0;
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
    s[1] = '\0';

    //Get Function Name
    if (isalpha(c))
    {
        while (isalpha(s[++i] = c = getch()))
            ;
        s[i] = '\0';
        ungetch(c);
        return FUNCTION;
    }

    //Get Number
    if (isdigit(c))
    {
        while(isdigit(s[++i] = c = getch()))
            ;
        if (c == '.')
        {
            //unsupport float: 123.123e-2
            while(isdigit(s[++i] = c = getch()))
                ;
        }
        s[i] = '\0';
        ungetch(c);
        return NUMBER;
    }

    return c;
}

void DealFunction(char *s)
{
    int i = 0;
    double temp = 0.0;
    for (; s[i] != '\0'; ++i)
    {
        s[i] = tolower(s[i]);
    }

    if (!strcmp(s, "sin"))
    {
        printf("Do SIN.\n");
        push(sin(pop()));
    }
    else if (!strcmp(s, "cos"))
    {
        printf("Do COS.\n");
        push(cos(pop()));
    }
    else if (!strcmp(s, "exp"))
    {
        printf("Do EXP.\n");
        push(exp(pop()));
    }
    else if (!strcmp(s, "pow"))
    {
        printf("Do POW.\n");
        temp = pop();
        push(pow(pop(), temp));
    }
    else
    {
        printf("Unsupport function!\n");
    }
}

