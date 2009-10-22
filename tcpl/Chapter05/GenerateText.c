#include <string.h>
#include <stdio.h>

#define MAX_STRING_LENGTH   10000
#define MAX_CIRCLE   1

static char buffer[MAX_STRING_LENGTH];
static int bufferindex;

int getline(char *str, int length);
char *alloc(int length);

/*atoi();
itoa();
reverse();
strindex();
getop();*/

int main()
{
    char str[100];
    int max = MAX_CIRCLE;
    char *strs[100];
    int i, j;
    //while (max-- > 0)
    {
        int len = 0;
        i = 0;
        while ((len = getline(str, 100)) > 0)
        {
            strs[i] = alloc(len);
            if (strs[i] != NULL)
            {
                strcpy(strs[i++], str);
            }
            else
                break;
        }

        for (j = 0; j < i; ++j)
            printf("%s", strs[j]);
    }
    return 0;
}

//get a line, return the length
int getline(char *str, int length)
{
    char *temp = str;
    while (length-- > 0 && (*str = getchar()) != '\n' && *str != EOF)
    {
        ++str;
    }
    *++str = '\0';
    return str - temp - 1;
}

char *alloc(int length)
{
    if (bufferindex + length + 1 < MAX_STRING_LENGTH)
    {
        bufferindex += length + 1;
        return buffer + bufferindex - length - 1;
    }
    return NULL;
}
