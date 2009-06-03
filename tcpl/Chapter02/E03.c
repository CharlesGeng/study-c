/*
 * Convert HEX string to interger
 * 
 * */

#include <stdio.h>

int htoi(char *val);
void ShowUseage();

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        ShowUseage();
        return 0;
    }
    else
    {
        printf("%d\n", htoi(argv[1]));
    }
    return 0;
}

// Show Help
void ShowUseage()
{
    printf("Uesage: E03 [HEX Number String]\n");
}

//Converter
int htoi(char *val)
{
    unsigned long long result = 0;
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
