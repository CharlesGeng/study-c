#include <stdio.h>

//存放括号

void formatparentheses(int[], int);

int main()
{
    //总记录数
    int count = 0;
    //括号数
    int parentheses = 0;
    int data[40];
    int i = 0;
    int j = 0;
    //获取总记录数
    scanf("%d\n", &count);
    for (i = 0; i < count; ++i)
    {
        scanf("%d\n", &parentheses);
        for (j = 0; j < parentheses; ++j)
        {
            scanf("%d ", &data[j]);
        }
        formatparentheses(data, parentheses);
    }
    return 0;
}


void formatparentheses(int parentheses[], int count)
{
    char cparentheses[100];
    int i = 0;
    int j = 0;

    int temp = parentheses[i];
    while (temp-- > 0)
        cparentheses[j++]='(';
    cparentheses[j++] = ')';

    for (i = 1; i < count; ++i)
    {
        temp = parentheses[i] - parentheses[i-1];
        while(temp-- > 0)
        {
            cparentheses[j++]='(';
        }
        cparentheses[j++] = ')';
    }

    for (i = 0; i < j; ++i)
    {
        printf("%c", cparentheses[i]);
    }
    printf("\n");
}
