/* BUG:
 *      1.if there are other symbols, such as single quotes, double quotes
 *      the program won't recgnize the words.
 * */
#include <stdio.h>
//#include <ctype.h>

int main()
{
    char c;
    int nchar, nline, nword;
    nchar = nline = nword = 0;
    while ((c = getchar()) != EOF)
    {
        nchar++;
        if (c == '\n')
        {
            ++nline; 
        }
    }
    printf("character:%d line:%d word:%d", nchar, nline, nword);
}
