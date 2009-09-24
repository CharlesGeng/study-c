#include <stdio.h>
#include <string.h>
#include <ctype.h>

void GetPN(char *src, char *phone);

static char *phoneArray[100000];
static int counter[100000];

int main()
{
    char src[33];
    char dst[10];
    int count = 0;
    int i = 0;
    int j = 0;
    scanf("%d", &count);
    if (count > 0)
    {
        i = 0;
        while (scanf("%s", src) == 1)
        {
            GetPN(src, dst);
            //check if the array Exsit the number
            for (j = 0; j < i; ++j)
            {
                if (strcmp(dst, phoneArray[j]) == 0)
                {
                    ++counter[j];
                    break;
                }
            }
            //not exsit
            if (j == i)
            {
                strcpy(phoneArray[j], dst);
                counter[j] = 1;
                ++i;
            }
        }

        for (j = 0 ; j < i; ++j)
        {
            if (counter[j] > 1)
            {
                printf("%s %d\n", phoneArray[j], counter[j]);
            }
        }
    }
    return 0;
}

void GetPN(char *src, char *phone)
{
    int i = 0;
    int j = 0;
    while (src[i] != '\0')
    {
        if (j == 3)
            phone[j++] = '-';
        if (isalpha(src[i]))
        {
            if (src[i] < 'Q')
                phone[j++] = (src[i] - 'A') / 3 + 2 + 0x30;
            else if (src[i] < 'Z')
                phone[j++] = (src[i] - 'A' - 1) / 3 + 2 + 0x30;
        }
        else if (isdigit(src[i]))
        {
            phone[j++] = src[i];
        }
        ++i;
    }
    phone[j] = '\0';
}
