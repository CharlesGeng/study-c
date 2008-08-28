#include <stdio.h>

void expandex (char s1[], char s2[])
{
    int i = 0;
    int j = 0;
    char c ;
    while ( (c = s1[i++]) != '\0')
    {
        if ( s1[i] == '-' && s1[i+1] >=c)
        {
            i++;
            while(c < s1[i])
            {
                s2[j++] = c++;
            }
        }
        else
        {
            s2[j++] = c;
        }
    }
    s2[j] = '\0';
}

int main()
{
    char *test = "a-e-j";
    char result[1024];
    expandex(test, result);
    printf("%s\n", test);
    printf("%s\n", result);
    test = "0-9a-z";
    expandex(test, result);
    printf("%s\n", test);
    printf("%s\n", result);
    test = "-a-z";
    expandex(test, result);
    printf("%s\n", test);
    printf("%s\n", result);
    return 0;
}
