/*
 * =====================================================================================
 *
 *       Filename:  E10.c
 *
 *    Description:  Excercise 10, just For + - * /
 *
 *        Version:  1.0
 *        Created:  2009年12月04日 17时55分44秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Neil Gunn (moomu), gengqi.cn@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXARGUMENTS 100
#define MINARGUMENTS 4

int DATA[MAXARGUMENTS];
int INDEX;

//push data into the stack
void push(int data)
{
    if(INDEX < MAXARGUMENTS)
        DATA[INDEX++] = data;
    else
        printf("The stack is Full!\n");
}

//pop up data from the stack
int pop()
{
    if (INDEX > 0)
        return DATA[--INDEX];
    printf("Pop error, the stack is empty!\n");
    return -1;
}

void Calculate(char c)
{
    switch(c)
    {
        case '+':
            push(pop() + pop());
            break;
        case '-':
            {
            int temp = pop();
            push(pop() - temp);
            break;
            }
        case '*':
            {
            push(pop() * pop());
            break;
            }
        case '/':
            {
            int temp = pop();
            push(pop() / temp);
            break;
            }
        default:
            {
            printf("Unsupport charactor: %c\n", c);
            break;
            }
    }
}

int main(int argc, char *argv[])
{
    INDEX = 0;
    if(argc < MINARGUMENTS || argc > MAXARGUMENTS)
    {
        printf("Arguments error!\n");
        return -1;
    }
    while(--argc > 0)
    {
        char c;
        if (isdigit(c = (*++argv)[0]))
        {
            char *str = *argv;
            push(atoi(str));
        }
        else
        {
            Calculate(c);
        }
    }
    //print the result
    printf("The result is: %d\n", pop());
    return 0;
}


