/*
 * This Programe is used to convert tabstop and newline to '\t' and '\n',
 * Convert '\t' and '\n' to tabstop and newline
 *
 * BUG:
 * 1.Couldn't deal with the char '\t' and '\n' in Comments string
 *
 * Modified at:
 *      2009-06-05
 *      by Neil Gunn
 * */

#include "GetLine.h"

void escape (char s[], char t[]);
void unescape (char s[], char t[]);

int main()
{
    char s[MAXLENGTH];
    char t[MAXLENGTH];
    char tt[MAXLENGTH];
    while (GetLine(s, MAXLENGTH) > 0)
    {
        printf ("ORIGINAL: %s", s);
        escape (s, t);
        printf ("ESCAPED: %s\n", t);
        unescape (t, tt);
        printf ("UNESCAPED: %s\n", tt);
        printf ("\n");
    }
    return 0;
}

void escape (char *s, char *t)
{
    int i = 0;
    int j = 0;
    for (; s[i] != '\0'; ++i)
    {
        switch (s[i])
        {
            case '\t':
                t[j++] = '\\';
                t[j++] = 't';
                break;
            case '\n':
                t[j++] = '\\';
                t[j++] = 'n';
                break;
            default:
                t[j++] = s[i];
                break;
        }
    }
    t[j] = '\0';
}

void unescape (char *s, char *t)
{
    int i = 0;
    int j = 0;
    for (; s[i] != '\0'; ++i)
    {
        switch (s[i])
        {
            case '\\':
                switch (s[i+1])
                {
                    case 't':
                        t[j++] = '\t';
                        ++i;
                        break;
                    case 'n':
                        t[j++] = '\n';
                        ++i;
                        break;
                    default:
                        t[j++] = s[i++];
                        t[j++] = s[i];
                        break;
                }
                break;
            default:
                t[j++] = s[i];
                break;
        }
    }
    t[j] = s[i];
}
