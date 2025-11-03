#include <stdio.h>
#include <ctype.h>

int
isleap(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

/* atoi_v1: convert s to integer */
int
atoi_v1(char s[])
{
    int i, n;

    n = 0;
    for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
        n = 10 * n + (s[i] - '0');
    return n;
}

/* atoi_v2: convert s to integer */
int
atoi_v2(char s[])
{
    int n = 0;

    for (int i = 0; isdigit(s[i]); ++i)
        n = 10 * n + (s[i] - '0');
    return n;
}


/* ascii_table: print all printable ASCII characters with its code */
void
ascii_table(void)
{
    int j = 1;

    for (int i = 0; i < 128; ++i) {
        if (isprint(i)) {
            printf("%3d %c%s", i, i, (j % 10) == 0 ? "\n" : " ");
            ++j;
        }
    }
    printf("\n");
}

/* lower: convert c to lower case; ASCII only */
int
lower(int c)
{
    if (c >= 'A' && c <= 'Z')
        return c - 'A' + 'a';
    else
        return c;
}

/* squeeze: delete all c from s */
void
squeeze(char s[], int c)
{
    int i, j;

    for (i = j = 0; s[i] != '\0'; i++) {
        if (s[i] != c)
            s[j++] = s[i];
    }
    s[j] = '\0';
}

/* cpl_strcat: concatenate t to end of s; s must be big enough */
void
cpl_strcat(char s[], char t[])
{
    int i, j;

    i = j = 0;
    while (s[i] != '\0')    /* find end of s */
        i++;
    while ((s[i++] = t[j++]) != '\0')   /* copy t */
        ;
}

/* bitcount: count 1 bits in x */
int bitcount(unsigned x)
{
    int b;

    for (b = 0; x != 0; x >>= 1)
        if (x & 01)
            b++;
    return b;
}
