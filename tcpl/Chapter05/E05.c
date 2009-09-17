#include <stdio.h>

//int strend(char *s, char *t);
int strlen(char *s);
char *strncpy(char *s, char *ct, int n);
char *strncat(char *s,char *ct,int n);
int strncmp(char *cs,char *ct,int n);

int main()
{
	char s[1000];
	char t[1000];
	int len = 0;
	while (scanf("%s%s%d",s, t, &len) == 3)
	{
		printf("%d\n", strncmp(s, t, len));
	}
    return 0;
}

//copy at most n characters of string ct to s; return s. Pad with '\0''s if ct has fewer than n characters.
char *strncpy(char *s, char *ct, int n)
{
	int i = 0;
	int len = strlen(ct);
	if (len > n)
		len = n;
	for (i = 0; i < len; ++i)
	{
		s[i] = ct[i];
	}
	s[i] = '\0';
	return s;
}

//concatenate at most n characters of string ct to string s, terminate s with '\0'; return s.
char *strncat(char *s,char *ct,int n)
{
    int i = 0;
    int s_len = strlen(s);
    int len = strlen(ct);
    len = (len < n) ? len : n;
    for (;i < len; ++i)
        s[s_len + i] = ct[i];
    s[s_len + i] = '\0';
    return s;
}

//compare at most n characters of string cs to string ct; return <0 if cs<ct, 0 if cs==ct, or >0 if cs>ct.
int strncmp(char *cs,char *ct,int n)
{
    int min = strlen(ct);
    min = (min < n ) ? min : n;
    while (min -- > 0)
    {
        if (*cs != *ct || *cs == '\0')
            return *cs - *ct;
        else
        {
            cs++;
            ct++;
        }
    }
    return 0;
}

int strlen(char *s)
{
	int i = 0;
	while (s[i])
		++i;
	return i;
}
