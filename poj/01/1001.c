#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//functions
void Mult(char *, char *, char *);
void RemoveZeros(char *rst);

int main()
{
    int n;
    char R[100];
    char temp[1000];
    char result[1000];
    int i = 0;
    while(scanf("%s%d", R, &n) == 2)
    {
        if (atof(R) == 0.0)
            strcpy(result, "0");
        else
            strcpy(result, "1");

        for (i = 0; i < n; ++i)
        {
            strcpy(temp, result);
            Mult(temp, R, result);
        }
        RemoveZeros(result);
        printf("%s\n", result);
    }
    return 0;
}

void Mult(char *A, char *B, char *rst)
{
    char Result[100][1000];
    int pa  = strlen(A);        //store the index of point in A;
    int pb  = strlen(B);        //store the index of point in B;
    int iA  = pa - 1;
    int iB  = pb - 1;
    int j   = 0;
    int l   = 0;
    int x   = 0;
    int len = 0;
    int pi = 0;

    rst[0] = '\0';
    for (; iB >= 0; --iB)
    {
        if (B[iB] >='0' && B[iB] <= '9')
        {
            int b = B[iB] - '0';
            int flag = 0;

            int k = 0;

            //set zeros
            for (; k < l; ++k)
            {
                Result[l][k] = '0';
            }

            //multiply
            for (j = iA; j >= 0; --j)
            {
                if (A[j] >= '0' && A[j] <= '9')
                {
                    int temp = (A[j] - '0') * b + flag;
                    Result[l][k++] = temp % 10 + '0';
                    flag = temp / 10;
                }
                else if (A[j] == '.')
                    pa = j;
            }
            while (flag > 0)
            {
                Result[l][k++] = flag % 10 + '0';
                flag /= 10;
            }
            Result[l][k] = '\0';
            ++l;
        }
        else if (B[iB] == '.')
            pb = iB;
    }

    //sum data
    strcpy(rst, Result[0]);
    if (pb < strlen(B))
    {
        len = strlen(B) - 1;
    }
    else
    {
        len = strlen(B);
    }
    for (x = 1; x < len; ++x)
    {
        int index = 0;
        int flag = 0;
        int rstLEN = strlen(rst);
        int riLEN  = strlen(Result[x]);
        for (; index < riLEN; ++index)
        {
            int temp = 0;
            if (index < rstLEN && rst[index] >= '0' && rst[index] <= '9')
                temp = rst[index] - '0' + Result[x][index] - '0' + flag;
            else
                temp = Result[x][index] - '0'+ flag;
            rst[index] = temp % 10 + '0';
            flag = temp / 10;
        }
        while (flag > 0)
        {
            rst[index++] = flag % 10 + '0';
            flag /= 10;
        }
        if (index >= rstLEN)
            rst[index] = '\0';
    }

    //revert result string
    len = strlen(rst);
    for (x = 0; x < len / 2; ++x)
    {
        int temp = rst[x];
        rst[x] = rst[len - x - 1];
        rst[len - x - 1] = temp;
    }

    //set point
    if(pa < strlen(A))
        pi = strlen(A) - pa - 1;
    if (pb < strlen(B))
        pi += strlen(B) - pb - 1;
    for (x = 0; x < pi; ++x)
    {
        rst[len - x] = rst[len - x - 1];
    }
    rst[len + 1] = '\0';

    rst[len - pi] = '.';
}

void RemoveZeros(char *rst)
{
    int len = strlen(rst);
    int pi = -1;
    int i = 0;

    //get the index of point
    while (rst[i] != '\0')
    {
        if (rst[i] == '.')
        {
            pi = i;
            break;
        }
        ++i;
    }

    //have point, remove the tail of zeros.
    if (pi != -1)
    {
        for (i = len - 1; i >= pi; --i)
        {
            if (rst[i] == '0')
            {
                rst[i] = '\0';
                continue;
            }
            else if (rst[i] == '.')
            {
                rst[i] = '\0';
                break;
            }
            else
            {
                break;
            }
        }
    }

    //remove the head of zeros.
    for (i = 0; i < len - pi; ++i)
    {
        if (rst[i] != '0')
            break;
    }

    if (i > 0 && rst[i] != '\0')
    {
        int j = i;
        while (rst[j] != '\0')
        {
            rst[j - i] = rst[j];
            ++j;
        }
        rst[j - i] = '\0';
    }
}
