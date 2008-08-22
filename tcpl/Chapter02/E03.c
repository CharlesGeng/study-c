#include <stdio.h>

int htoi(char *val);

int main()
{
    printf("%d\n", htoi("0xFFFF"));
    return 0;
}

int htoi(char *val)
{
    int result = 0;
    int i;
    if (val[0] == '0' && (val[1] == 'X' || val[1] == 'x'))
    {
        for (i = 2; val[i] != '\0'; ++i)
        {
            if (val[i] >= '0' && val[i] <='9')
            {
                result = result * 16 + val[i] - '0';
            }
            else if(val[i] >= 'a' && val[i] <='f') 
            {
                result = result * 16 + 10 + val[i] - 'a';
            }
            else if(val[i] >= 'A' && val[i] <='F') 
            {
                result = result * 16 + 10 + val[i] - 'A';
            }
        }
    }
    return result;
}
