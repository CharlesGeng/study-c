#include<stdio.h>

#define MAXLENGTH   1000

int getline(char string[]);

int main()
{
    int len = 0;
    char line[MAXLENGTH];
    while ((len = getline(line)) > 0)
    {
        if (len < 2)
            continue;
        else
        printf("%s", line);
    }
    return 0;
}

int getline(char line[]) 
{
    int i = 0;
    char c;
    int j = 0;
    while ((c = getchar()) != EOF && c != '\n')
    {
        line[i++] = c;
    }
    if (c == '\n')
        line[i++] = '\n';
    line[i] = '\0';
    if (i > 1)
    {
        for (j = i-2; j >= 0; --j)
        {
            if (line[j] != '\t' && line[j] != ' ')
            {  
                break;
            }
            else
            {
                line[j] = '\n';
                line[j+1] = '\0';
                i = j;
            }
        }
    }
    return i;
}
