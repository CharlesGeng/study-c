#include <stdio.h>
#include <ctype.h>

//CONSTANTS
#define R_MAX 99.999
#define R_MIN 0.0
#define R_LENGTH 7

#define n_MAX 25
#define n_MIN 0


//functions
char *calculate(char *, int);

int main()
{
    char R[R_LENGTH];
    int n;
    while(scanf("%s%d", R, &n) == 2)
    {
        ;
    }
    return 0;
}

char *calculate(char *R, int n)
{
    int i;
    int j;
    int Flag = 0;
    char result[1000] = *R;
    for(i = 0; i < n; ++i)
    {
        for (j = R_LENGTH - 1; j >= 0; ++j)
        {
            if (R[j] > '0' && R[j] <= '9')
        }
    }
}

void revertstr(char *str, int length)
{

}
