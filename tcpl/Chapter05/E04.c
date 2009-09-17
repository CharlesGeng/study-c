#include <stdio.h>

int strend(char *s, char *t);
int strlen(char *s);

int main()
{
    char s[100];
    char t[100];
    while (scanf("%s%s", s, t) == 2)
    {
        if (strend(s, t) == 0)
        {
            printf("yes!\n");
        }
        else
        {
            printf("No!\n");
        }
    }
    return 0;
}

int strend(char *s, char *t)
{
    int s_len = strlen(s);
    int t_len = strlen(t);
    if (t_len > 0 && t_len <= s_len)
    {
        for (--t_len, --s_len; t[t_len] == s[s_len] && t_len >= 0; t_len--, s_len--)
            ;
        if (t_len == -1)
            return 0;
    }
    return 1;
}

int strlen(char *s)
{
    int i = 0;
    while (s[i])
        ++i;
    return i;
}
