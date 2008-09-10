#include <stdio.h>

//Get the string's length
int strlength (char sf[])
{
    int i = 0;
    while (sf[i++] != '\0')
        ;
    return --i;
}

//if "SF" contains ss,then display the "SF"
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
            printf("%s\n", sf);
            return i;
        }
    }
    return -1;
}


int main()
{
    char *sf1 = "i could do anything.";
    char *sf2 = "this line include \"could\"";
    char *sf3 = "this line not\n";
    char *sf4 = "mycoulddcoul ould";
    strrindex(sf1, "could");
    strrindex(sf2, "could");
    strrindex(sf3, "could");
    strrindex(sf4, "could");
    return 0;
}
