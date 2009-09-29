#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define NUMBERLENGTH    9
#define MAXCOUNT        100000

int GetPhoneNumber(char *src, char *phone);

struct PhoneNumber{
    char    number[NUMBERLENGTH];
    int     count;
};

static struct PhoneNumber phones[MAXCOUNT];

int main()
{
    char src[33];
    char dst[NUMBERLENGTH];
    int count = 0;
    int i = 0;
    int j = 0;
    scanf("%d", &count);
    if (count > 0)
    {
        i = 0;
        while (scanf("%s", src) == 1)
        {
            if (( GetPhoneNumber(src, dst) + 1) == NUMBERLENGTH)
            {
                //check if the array Exsit the number
                for (j = 0; j < i; ++j)
                {
                    if (strlen(phones[j].number) > 0 &&
                            strcmp(dst, phones[j].number) == 0)
                    {
                        ++phones[j].count;
                        break;
                    }
                }
                //not exsit
                if (j == i)
                {
                    strcpy(phones[j].number, dst);
                    phones[j].count = 1;
                    ++i;
                }
            }
        }

        for (j = 0 ; j < i; ++j)
        {
            if (phones[j].count > 1)
            {
                printf("%s %d\n", phones[j].number, phones[j].count);
            }
        }
    }
    return 0;
}

int GetPhoneNumber(char *src, char *phone)
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
    return j;
}
