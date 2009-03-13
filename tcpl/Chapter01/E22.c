#include <stdio.h>

#define LINEMAX     2000        //the max lenth of a line
#define MAXLENGTH   20          //ideal length

int getline(char[], int);       //get a line
void splitline(char[], int);    //split line

int main()
{
    int i;
    char str[MAXLENGTH];

    while ((i = getline(str, LINEMAX)) > 0) 
    {
        if (i > MAXLENGTH)
        {
            splitline(str, MAXLENGTH);
        }
        else
        {
            printf("%s", str);
        }
    }
}

//initialize the line and return the length
int getline(char str[], int limit)
{
    int c;
    int i = 0;
    while (i < limit - 1 && EOF != (c = getchar()) && '\n' != c)
    {
        str[i++] = c;
    }

    if ('\n' == c)
    {
        str[i++] = '\n';
    }
    str[i] = '\0'; 
    return i;
}

void splitline(char str[], int maxlength)
{
    int i       = 0;
    int pos     = 0;
    int oldpos  = 0;

    while (str[i] != '\0')
    {
        if (str[i] == ' '|| str[i] == '\t')
        {
            pos = i;
        }
        if ((i + 1) % maxlength == 0)
        {
            if(pos > 0)     //can be splited
            {
                for (; oldpos <= pos; ++oldpos)
                {
                    putchar(str[oldpos]);
                }
                putchar('\n');
            }
            else            //out the line without splited
            {
                for (; oldpos < i; ++oldpos)
                {
                    putchar(str[oldpos]);
                }
            }
        }
        ++i;
    }

    if (i % maxlength != 0)
    {
        for (; oldpos < i - 1; ++oldpos)
        {
            putchar(str[oldpos]);
        }
    }
}
