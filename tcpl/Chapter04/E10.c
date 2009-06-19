#include "calculator.h"

#define SUCCESS     0
#define FAILURE     1

#define NUMBER      0
#define FUNCTION    1


void calc(int type)
{
    double op2 = 0.0;
    switch(type) {
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop()*pop());
            break;
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
        case '%':
            op2 = pop();
            if(op2 != 0.0)
                push(fmod(pop(), op2));
            else
                printf("error:zero divisor\n");
            break;
        case '\n':
            printf("\t%.8g\n",pop());
            break;
        default:
            printf("error:unknown command %s\n",type);
            break;
    }
}

//get a line
//return  the length of line
int getline(char *str)
{
    int c = 0;
    int i = 0;
    while (i < MAXLENGTH && (c = getchar()) != EOF && c != '\n')
    {
        str[i++] = c;
    }

    if (c == '\n')
        str[i++] = '\n';
    str[i] = '\0';
    return i;
}

//calculate
//return SUCCESS or FAILURE
int doline(char *s)
{
    int i = 0;
    int j = 0;
    char temp[MAXLENGTH];

    while (i < MAXLENGTH && s[i] != '\n' && s[i] != EOF)
    {
        j = 0;
        //skip blank
        while (s[i] == ' '|| s[i] == '\t')
        {
            ++i;
        }

        // do + - * /
        if (!isdigit(s[i]) && s[i] != '.')
        {
            calc(s[i]);
            ++i;
            continue;
        }

        //Get Number
        if (isdigit(s[i]))
        {
            while (isdigit(temp[j++] = s[i++]))
                ;
        }

        if (s[i - 1] == '.')
        {
            while (isdigit(temp[j++] = s[i++]))
                ;
        }

        temp[j - 1] = '\0';
        push(atof(temp));
    }
    if (i > 0)
        return SUCCESS;
    else
        return FAILURE;
}

int main()
{
    int length = 0;
    char str[MAXLENGTH];

    while ((length = getline(str)) > 0)
    {
        if (doline(str) == SUCCESS)
            printf("\t%.8g\n", pop());
        else
            printf("Calculate ERROR!\n");
    }
    return 0;
}

