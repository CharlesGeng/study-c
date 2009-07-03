#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#define MAXLENGTH   1000
#define NAMELENGTH	10

typedef struct
{
    char name[NAMELENGTH];
    double value;
}variable;

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
void ungets(char *s);
