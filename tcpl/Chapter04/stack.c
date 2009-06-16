#include "calculator.h"

static double stack[MAXLENGTH];         //the stack
int si;						//index of the stack

/*
 * pop up a charactor from the stack;
 * */
double pop(void)
{
    if (si > 0)
    {
        return stack[--si];
    }
    else
    {
        printf("POP ERROR: The stack is empty!\n");
        return 0.0;
    }
}

/*
 * push a charactor into the stack
 * */
void push(double c)
{
    if (si < MAXLENGTH)
        stack[si++] = c;
    else
    {
        printf("PUSH ERROR: The stack is full!\n");
    }
}

/*
 * show the top element
 * */
void showtop()
{
    if (si > 0)
    {
        printf("%.8g\n", stack[si - 1]);
    }
    else
    {
        printf("SHOWTOP ERROR: The stack is empty!\n");
    }
}

/*
 * swap top two elements
 * */
void swaptop()
{
    double top1;
    double top2;
    if (si > 1)
    {
        top1 = pop();
        top2 = pop();    
        push(top1);
        push(top2);
    }
    else
    {
        printf("SWAP ERROR: There is no more than two elements in the stack!\n");
    }
}

void duplicatetop()
{
    double top = pop();
    if (si < 1)
    {
        printf("DUPLICATE ERROR: The stack is empty!\n");
    }
    else if (si > MAXLENGTH - 2)
    {
        printf("DUPLICATE ERROR: There is no space to store new element!\n");
    }
    else
    {
        double top = pop();
        push (top);
        push (top);
    }
}

/*
 * clear the stack
 * */
void clear()
{
    si = 0;
}
