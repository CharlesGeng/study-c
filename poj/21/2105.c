#include<stdio.h>
#include<ctype.h>

void formatIP(char *src, char *dst);

int main()
{
    int N = 0;
    char data[33];
    char result[17];
    scanf("%d", &N);
    while( N-- > 0)
    {
        scanf("%s", data);
        formatIP(data, result);
    }
    return 0;
}

void formatIP(char *src, char *dst)
{
    dst = '\0';
    int i = 0;
    int temp = 0;
    for(i = 0; i < 33; ++i)
    {
        if (src[i] == '1')
        {
            temp = temp | (1 << (7 - i % 8));
        }
        if (((i+1) % 8) == 0)
        {
            if (i == 31)
                printf("%d", temp);
            else
                printf("%d.", temp);
            temp = 0;
        }
    }
    printf("\n");
}
