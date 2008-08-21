#include <stdio.h>
#include <string.h>

#define lim 10

int main()
{
    int i;
    char c;
    //Original
    for(i=0; i<lim-1&&(c=getchar())!='\n'&&c!=EOF; ++i)
    {
        //DO SOMETHING
    }
    //Destination "FOR" version
    for (i=0; ; ++i)
    {
        if (i < lim-1)
        {
            if ((c=getchar())!='\n')
            {
                if (c != EOF)
                {
                    //DO SOMETHING
                }
                else
                {
                    break;
                }
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }

    //Destination "FOR" version
    i = 0;
    while (i < lim-1)
    {
        if ((c=getchar())!='\n')
        {
            if (c != EOF)
            {
                //DO SOMETHING
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }

    }
    return 0;
}

