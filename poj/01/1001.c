#include <stdio.h>
#include <string.h>
#include <ctype.h>

//CONSTANTS
#define R_LENGTH        7
#define R_DATALENGTH    5

//functions
void Mult(char *, char *, char *);

int main()
{
    char result[1000];
    /*char R[R_LENGTH];
    int n;
    char temp[1000];
    while(scanf("%s%d", R, &n) == 2)
    {
        int i = 1;
        strcpy(result, R);
        for (; i < n; ++i)
        {
            strcpy(temp, result);
            Mult(temp, R, result);
        }
    }
    */
    Mult("95.123", "95.123", result);
    return 0;
}

void Mult(char *A, char *B, char *rst)
{
    char Result[R_DATALENGTH][1000];
    int iA  = strlen(A) - 1;
    int iB  = strlen(B) - 1;
    int j   = 0;
    int l   = 0;
    int maxlen = 0;
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
                    Result[l][k++] = temp % 10 + 0x30;
                    flag = temp / 10;
                }
            }
            while (flag > 0)
            {
                Result[l][k++] = flag % 10 + 0x30;
                flag /= 10;
            }
            Result[l][k] = '\0';
            maxlen = maxlen > k ? maxlen : k;
            ++l;
        }
    }

    strcpy(rst, Result[0]);
    int x = 1;
    for (; x < R_DATALENGTH; ++x)
    {
        int index = 0;
        int flag = 0;
        int rstLEN = strlen(rst);
        int riLEN  = strlen(Result[x]);
        for (; index < riLEN; ++index)
        {
            int temp = 0;
            if (rst[index] >= '0' && rst[index] <= '9')
                temp = rst[index] - 0x30 + Result[x][index] - 0x30 + flag;
            else
                temp = Result[x][index] - 0x30 + flag;
            rst[index] = temp % 10 + 0x30;
            flag = temp / 10;
        }
        while (flag > 0)
        {
            rst[index++] = flag % 10 + 0x30;
            flag /= 10;
        }
        if (index >= rstLEN)
            rst[index] = '\0';
    }
    printf("%s\n", rst);
}

//remove zeros
void FormatResult(char *result)
{
    //TODO
}
