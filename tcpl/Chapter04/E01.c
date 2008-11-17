#include <stdio.h>

#define MAXLINE 100

int strlength(char str[])
{
    int l = 0;
    while (str[l++] != '\0')
        ;
    return --l;
}

//if "SF" contains partern "ss",then display the "SF"
int strrindex(char sf[], char ss[])
{
    int fl = strlength(sf);
    int sl = strlength(ss);
    int i = fl - sl;
    int j = 0;
    for (; i >= 0; --i)
    {
        for (; sf[i+j] == ss[j] && ss[j] != '\0'; ++j)
        {}
        if (ss[j] == '\0')
        {
            printf("%d\n", i);
            printf("%s", sf);
            return i;
        }
    }
    return -1;
}

int getline(char line[], int length)
{
    int i, c;
    i = c = 0;
    while(--length > 0 && (c = getchar()) != EOF && c != '\n')
        line[i++] = c;
    if (c == '\n')
        line[i++] = '\n';
    line[i] = '\0';
    return i;
}

int main()
{
    char line[MAXLINE];
    char *partern = "ould";
    while(getline(line, MAXLINE) > 0)
        strrindex(line, partern);
    return 0;
}
