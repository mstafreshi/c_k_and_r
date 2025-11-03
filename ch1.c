#include <stdio.h>
#include "cpl.h"
#include "ch1.h"


void
fahr_to_celsius_v1(void)
{
    int fahr, celsius;
    int lower, upper, step;

    PRINT_FUNCTION_INFO;

    lower = 0;
    upper = 300;
    step = 20;

    fahr = lower;
    while (fahr <= upper) {
        celsius = 5 * (fahr - 32) / 9;
        printf("%d\t%d\n", fahr, celsius);
        fahr = fahr + step;
    }
}

void
fahr_to_celsius_v2(void)
{
    float fahr, celsius;
    int lower, upper, step;

    PRINT_FUNCTION_INFO;

    lower = 0;
    upper = 300;
    step = 20;

    fahr = lower;
    while (fahr <= upper) {
        celsius = (5.0 / 9.0) * (fahr - 32.0);
        printf("%3.0f %6.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
}

void
fahr_to_celsius_v3(void)
{
    int fahr;

    PRINT_FUNCTION_INFO;

    for (fahr = 0; fahr <= 300; fahr = fahr + 20)
        printf("%3d %6.1f\n", fahr, (5.0 / 9.0) * (fahr - 32));
}

/* fahr_to_celsius_v4: print Fahrenheit-Celsius table version 4 */
void
fahr_to_celsius_v4(void)
{
    int fahr;

    PRINT_FUNCTION_INFO;

    for (fahr = LOWER; fahr <= UPPER; fahr = fahr + STEP)
        printf("%3d %6.1f\n", fahr, (5.0 / 9.0) * (fahr - 32));
}

/* copy_v1: copy input to output */
void
copy_v1(void)
{
    int c;

    PRINT_FUNCTION_INFO;

    c = getchar();
    while (c != EOF) {
        putchar(c);
        c = getchar();
    }
}

/* copy_v2: copy input to output */
void
copy_v2(void)
{
    int c;

    PRINT_FUNCTION_INFO;

    while ((c = getchar()) != EOF)
        putchar(c);
}

/* nc_v1: count characters in input; 1st version */
void
nc_v1(void)
{
    long nc;

    PRINT_FUNCTION_INFO

    nc = 0;
    while (getchar() != EOF)
        ++nc;
    printf("%ld\n", nc);
}

/* nc_v2: count characters in input: 2nd version */
void
nc_v2(void)
{
    double nc;

    PRINT_FUNCTION_INFO

    for (nc = 0; getchar() != EOF; ++nc)
        ;
    printf("%.0f\n", nc);
}

/* nl: count lines in input */
void
nl(void)
{
    int c, nl;

    PRINT_FUNCTION_INFO

    nl = 0;
    while ((c = getchar()) != EOF)
        if (c == '\n')
            ++nl;
    printf("%d\n", nl);
}

/* wc */
void
wc(void)
{
    int c, nl, nw, nc, state;

    PRINT_FUNCTION_INFO

    state = OUT;
    nl = nw = nc = 0;
    while ((c = getchar()) != EOF) {
        ++nc;
        if (c == '\n')
            ++nl;
        if (c == ' ' || c == '\n' || c == '\t')
            state = OUT;
        else if (state == OUT) {
            state = IN;
            ++nw;
        }
    }
    printf("%d %d %d\n", nl, nw, nc);
}

/* count_digit_whitespace_other */
void
count_digit_whitespace_other(void)
{
    int c, i, nwhite, nother;
    int ndigit[10];

    PRINT_FUNCTION_INFO

    nwhite = nother = 0;
    for (i = 0; i < 10; ++i)
        ndigit[i] = 0;

    while ((c = getchar()) != EOF)
        if (c >= '0' && c <= '9')
            ++ndigit[c - '0'];
        else if (c == ' ' || c == '\n' || c == '\t')
            ++nwhite;
        else
            ++nother;

    printf("digits =");
    for (i = 0; i < 10; i++)
        printf(" %d", ndigit[i]);
    printf(", white space = %d, other = %d\n", nwhite, nother);
}

/* power_v1: raise base to n-th power; n >= 0 */
int
power_v1(int base, int n)
{
    int i, p;

    p = 1;
    for (i = 1; i <= n; i++)
        p = p * base;
    return p;
}

/* power_v2: raise base to n-th power; version 2 */
int
power_v2(int base, int n)
{
    int p;

    for (p = 1; n > 0; --n)
        p = p * base;
    return p;
}

/* cpl_getline_v1: read a line into s, return length */
int
cpl_getline_v1(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;

}

/*copy: copy 'from' into 'to'; assume to is big enough */
void
copy(char to[], char from[])
{
    int i;

    i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}


/* print_longest_line: read all line from stdin and prints longest line */
void
print_longest_line(void)
{
    int len;
    int max;
    char line[MAXLINE];
    char longest[MAXLINE];

    max = 0;
    while ((len = cpl_getline(line, MAXLINE)) > 0)
        if (len > max) {
            max = len;
            copy(longest, line);
        }
    if (max > 0)    /* there was a line */
        printf("%s", longest);
}

/* specialized_cpl_getline: specialized version of cpl_getline */
int
specialized_cpl_getline(void)
{
    int c, i;
    // extern char line[]; // already defined in ch1.h

    for (i = 0; i < MAXLINE - 1
        && (c = getchar()) != EOF && c != '\n'; ++i)
            line[i] = c;
    if (c == '\n') {
        line[i] = c;
        ++i;
    }
    line[i] = '\0';
    return i;
}

/* specialized_copy: specialized version of copy */
void
specialized_copy(void)
{
    int i;
    // extern char line[], longest[]; // already defined in ch1.h

    i = 0;
    while ((longest[i] = line[i]) != '\0')
        ++i;
}

/* specialized_print_longest_line */
void
specialized_print_longest_line(void)
{
    int len;
    // extern char longest[]; // already defined in ch1.h

    while ((len = specialized_cpl_getline()) > 0)
        if (len > max) {
            max = len;
            specialized_copy();
        }
    if (max > 0)    /* there was a line */
        printf("%s", longest);
}
