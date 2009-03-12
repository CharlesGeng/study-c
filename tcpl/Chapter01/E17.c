/*
 * Print the line which is more than 80 charactors
 * 
 * */
#include <stdio.h>

#define MAXLENGHT   1000
#define LONGLINE    80

int getline(char str[]);

int main()
{
    char longest[MAXLENGHT ];  //Longest String
    char str[MAXLENGHT];
    int max = 0;    //Longest String's Length
    int len = 0;

    while ((len = getline(str)) > 0)
    {
        if (len > LONGLINE)
            printf("%d:%s", len, str);
    }
    return 0;
}

// Get Str's Length
int getline(char str[])
{
    char c;
    int i = 0;
    while ((c = getchar()) != EOF && c != '\n')
    {
        str[i++] = c;
    }
    if (c == '\n')
    {
        str[i++] = c;
    }
    str[i] = '\0';
    return i;
}
