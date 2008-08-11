//Reverse the Line
#include <stdio.h>

#define MAXLINE     1000

int reverseline(char line[]);

int main()
{
    char myline[MAXLINE];
    while (reverseline(myline) > 0)
        printf("%s", myline);
    return 0;
}

int reverseline(char line[])
{
    char c;
    int i, j;
    for (i = 0; (c = getchar()) != EOF && c != '\n'; ++i)
    {
        line[i] = c;
    }

    //REVERSE
    int k = i - 1;
    for (j = k; j > k/2; --j)
    {
        char temp = line[k-j];
        line[k-j] = line[j];
        line[j] = temp;
    }

    if (c == '\n')
        line[i++] = '\n';
    line[i] = '\0';
    return i;
}
