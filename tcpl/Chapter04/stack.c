#include "calculator.h"

#define MAXLENGTH   100    //the maximum length of the stack

static double stack[MAXLENGTH];         //the stack
static int index = 0;      //index of the stack

/*
 * pop up a charactor from the stack;
 * */
double pop(void)
{
    if (index > 0)
    {
        return stack[index--];
    }
    else
    {
        printf("ERROR: The stack is empty!");
        return 0.0;
    }
}

/*
 * push a charactor into the stack
 * */
void push(double c)
{
    if (index < MAXLENGTH)
        stack[index++] = c;
    else 
    {
        printf("ERROR: The stack is full!");
    }
}
