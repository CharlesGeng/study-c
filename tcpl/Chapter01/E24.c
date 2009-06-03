/*
 * Current Version: 0.1
 *
 * Description:
 *      This Program is used to check Syntax Error:
 *      1.Are brackets etc. matched
 * Created by : Neil Gunn
 *         at :
 *
 *  Modified by :
 *           at :
 *           log:
 * */

//parenthesis   ()
//bracket       []
//brace         {}

#include <stdio.h>

#define MAXLENGTH 1000

int _parCnt;
int _brkCnt;
int _brcCnt;

int GetLine(char * , int);
void CheckBracket(char *);

int main()
{
    char str[MAXLENGTH];
    while ((GetLine(str, MAXLENGTH)) > 0)
    {
        CheckBracket(str);
    }
    if (_parCnt != 0)
    {
        printf(_parCnt > 0 ? "The Source File Loss %d )\n" : "The Source File Loss %d (\n" , \
                _parCnt > 0 ? _parCnt : -_parCnt);
    }
    if (_brkCnt != 0)
    {
        printf(_brkCnt > 0 ? "The Source File Loss %d ]\n" : "The Source File Loss %d [\n" , \
                _brkCnt > 0 ? _brkCnt : -_brkCnt);
    }
    if (_brcCnt != 0)
    {
        printf(_brcCnt > 0 ? "The Source File Loss %d }\n" : "The Source File Loss %d {\n" , \
                _brcCnt > 0 ? _brcCnt : -_brcCnt);
    }
    if (_parCnt == 0 && _brkCnt == 0 && _brcCnt == 0)
        printf("There is nothing wrong in the source file!\n");

    return 0;
}

int GetLine(char *str, int length)
{
    int c = 0;
    char *start = str;
    while ((c = getchar()) != EOF && c != '\n')
        *str++ = c;
    if (c == '\n')
        *str++ = '\n';
    *str = '\0';
    return str - start;
}

void CheckBracket(char *str)
{
    int c = 0;
    int quoteFlag = 0;
    while ((c = *str++) != '\n' && c != EOF && c != '\0')
    {
        //in a string
        if (c != '"' && quoteFlag )
        {
            continue;
        }

        //begin or end of a string
        if (c == '"')
        {
            quoteFlag = !quoteFlag;
            continue;
        }

        switch (c)
        {
            case '(':
                _parCnt++;
                break;
            case ')':
                _parCnt--;
                break;
            case '[':
                _brkCnt++;
                break;
            case ']':
                _brkCnt--;
                break;
            case '{':
                _brcCnt++;
                break;
            case '}':
                _brcCnt--;
                break;
            default:
                break;
        }
    }
}
