#include <stdio.h>

void escape (char s[], char t[]);
void unescape (char s[], char t[]);

int main()
{
    char s[] = "abcd\tefgh\n";
    char t[100];
    char tt[100];
    escape (s, t);
    unescape (t, tt);
    return 0;
}

void escape (char s[], char t[])
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
    printf ("escaped:%s\n", t);
}

void unescape (char s[], char t[])
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
    printf ("unescaped:%s\n", t);
}
