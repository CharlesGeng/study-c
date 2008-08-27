#include <stdio.h>

void expand (char s1[], char s2[])
{
    int i = 0;
    for(; s2[i] != '\0'; ++i)
    {
        if (s2[i] == '-')
        {
            if(i > 0)
            {
                //a-z
                if (s2[i] >= 'a' && s2[i] <= 'z')
                {}
                //A-Z
                else if (s2[i] >= 'A' && s2[i] <= 'Z')
                {

                }
                //0-9
                else if (s2[i] >= '0' && s2[i] <= '9')
                {}
                //others
                else
                {}
            }
            else
            {

            }
        }
    }
}

int main()
{
    
    return 0;
}
