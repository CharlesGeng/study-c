#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define NUMBERLENGTH    9

typedef struct{
    char    *number;
    int     count;
}PhoneNumber;

int GetPhoneNumber(char *src, char *phone);
void myqsort(PhoneNumber numbers[], int left, int right);

int main()
{
    char src[50];
    int count = 0;
    int i = 0;
    int j = 0;
    scanf("%d", &count);
    if (count > 0)
    {
        char numbers[NUMBERLENGTH * count];
        char *dst = numbers;
        PhoneNumber phones[count];
        i = 0;
        while (scanf("%s", src) == 1)
        {
            if (( GetPhoneNumber(src, dst) + 1) == NUMBERLENGTH)
            {
                //check if the array Exsit the number
                for (j = 0; j < i; ++j)
                {
                    if (strcmp(dst, phones[j].number) == 0)
                    {
                        ++phones[j].count;
                        break;
                    }
                }
                //not exsit
                if (j == i)
                {
                    phones[j].number = dst;
                    phones[j].count = 1;
                    ++i;
                }
                dst += NUMBERLENGTH;
            }
        }

        //remove single phone numbers
        int k = 0;
        for (j = 0 ; j < i; ++j)
        {
            if (phones[j].count > 1)
            {
                phones[k++] = phones[j];
            }
        }

        //output results
        if (k > 0)
        {
            //sort the numbers
            myqsort(phones, 0, k - 1);
            for (j = 0; j < k; ++j)
                printf("%s %d\n", phones[j].number, phones[j].count);
        }
        else
        {
            printf("No duplicates.\n");
        }
    }
    return 0;
}

void swap(PhoneNumber numbers[], int x, int y)
{
    if (x != y)
    {
        PhoneNumber temp = numbers[x];
        numbers[x] = numbers[y];
        numbers[y] = temp;
    }
}

void myqsort(PhoneNumber numbers[], int left, int right)
{
    if (left < right)
    {
        int last = left;
        int i;
        swap(numbers, left, (left + right) / 2);
        for(i = left + 1; i <= right; ++i)
        {
            if (strcmp(numbers[i].number, numbers[left].number) < 0)
            {
                swap(numbers, ++last, i);
            }
        }
        swap(numbers, left, last);
        myqsort(numbers, left, last - 1);
        myqsort(numbers, last + 1, right);
    }
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
