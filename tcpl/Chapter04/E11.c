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
    static int c;
    int i = 0;

    if (c == 0)
        c = getchar();

    s[i] = '\0';

    //over blank charactor
    while ((s[i] = c) == ' ' || c == '\t')
         c = getchar();
    s[1] = '\0';

    //Get Function Name
    if (isalpha(c))
    {
        while (isalpha(s[++i] = c = getchar()))
            ;
        s[i] = '\0';
        return FUNCTION;
    }

    //Get Number
    if (isdigit(c))
    {
        while(isdigit(s[++i] = c = getchar()))
            ;
        if (c == '.')
        {
            //unsupport float: 123.123e-2
            while(isdigit(s[++i] = c = getchar()))
                ;
        }
        s[i] = '\0';
        return NUMBER;
    }

    if (c == '\n')
    {
        c = 0;
        return '\n';
    }
    else
    {
        return c;
    }
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

