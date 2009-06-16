#include <stdio.h>
#include <strings.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#define MAXLENGTH   1000



// Functions in stack.c
double pop();
void push(double);
void showtop();
void swaptop();
void duplicatetop();
void clear();

//Functions in getch.c
int getch();
void ungetch(int);
