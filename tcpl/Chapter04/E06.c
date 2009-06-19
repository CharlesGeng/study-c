/*
 * calculator just for sin, exp and power
 *
 * */

#include "calculator.h"

#define MAXVAR      100      //Variable array
#define NUMBER      '0'     //number
#define FUNCTION    '1'     //for sin exp power

void DealFunction(char *s, variable var[]);
int getop(char *s);

int _lastvarindex = 0;       // store the index of variable

int main()
{
    int result = 0;
	int i = 0;
    char s[MAXLENGTH];
    double temp = 0.0;
    variable var[MAXVAR];

	for (i = 0;i < MAXVAR; ++i)
	{
		var[i].name[0] = '\0';
	}

    while ((result = getop(s)) != EOF)
    {
        switch(result)
        {
            case NUMBER:
                push(atof(s));
                break;
            case FUNCTION:
                DealFunction(s, var);
                break;
            case '+':
                push(pop() + pop());
                break;
            case '-':
                temp = pop();
                push(pop() - temp);
                break;
            case '*':
                push(pop() * pop());
                break;
            case '/':
                temp = pop();
                if (temp != 0.0)
                {
                    push(pop() / temp);
                }
                else
                {
                    printf("Zero divisor!\n");
                }
                break;
            case '%':
                temp = pop();
                if (temp != 0.0)
                {
                    push(fmod(pop(), temp));
                }
                else
                {
                    printf("Zero divisor!\n");
                }
                break;
            case '!':
                clear();
                break;
            case '=':
                temp = pop();
                var[_lastvarindex].value = temp;
                push(temp);
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

//deal with variable
//*s variable name
//var[] array of variables
void Dealvariable(char *s, variable var[])
{
    int i = 0;

    //find variable
    for (i = 0; i < MAXVAR; ++i)
    {
        if (var[i].name[0] != '\0')
        {
            if (!strcmp(s, var[i].name))
            {
                push(var[i].value);
                return;
            }
        }
        else
        {
            break;
        }
    }

    //Add new variable
    _lastvarindex = i;
	strcpy(var[_lastvarindex].name, s);
    var[_lastvarindex].value = 0.0;
}

//deal with function
void DealFunction(char *s, variable ver[])
{
    int i = 0;
    double temp = 0.0;
    for (; s[i] != '\0'; ++i)
    {
        s[i] = tolower(s[i]);
    }

    if (!strcmp(s, "sin"))
    {
        push(sin(pop()));
    }
    else if (!strcmp(s, "cos"))
    {
        push(cos(pop()));
    }
    else if (!strcmp(s, "exp"))
    {
        push(exp(pop()));
    }
    else if (!strcmp(s, "pow"))
    {
        temp = pop();
        push(pow(pop(), temp));
    }
    else
    {
        Dealvariable(s, ver);
    }
}
