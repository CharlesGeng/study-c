#include <string.h>
#include <stdio.h>

#define MAX_STRING_LENGTH   10000
#define MAX_CIRCLE   10000

static char buffer[MAX_STRING_LENGTH];
static int bufferindex;

int GetLine(char *str, int length);
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
    int len = 0;
    i = 0;
    while ((len = GetLine(str, 100)) > 0)
    {
        strs[i] = alloc(len);
        if (strs[i] != NULL)
        {
            strcpy(strs[i++], str);
        }
        else
            break;
    }

    while (max-- > 0)
    {
        for (j = 0; j < i; ++j)
            printf("%s", strs[j]);
    }
    return 0;
}

//get a line, return the length
int GetLine(char *str, int length)
{
    char *temp = str;
    while (length-- > 0 && (*str = getchar()) != '\n' && *str != EOF)
    {
        ++str;
    }
    if (*str == '\n')
        *++str = '\0';
    else 
        *str = '\0';
    return str - temp ;
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
