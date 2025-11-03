#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "ch4.h"


char pattern[] = "ould";    /* pattern to search for */
char buf[BUFSIZE];          /* buffer for ungetch */
int  bufp = 0;              /* next free position in buf */
int  sp = 0;                /* next free stack position */
double val[MAXVAL];         /* value stack */

/* cpl_gteline_v2: get line into s, return length */
int
cpl_getline_v2(char s[], int lim)
{
    int c, i;

    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

/* strindex: return index of t in s, -1 if none */
int
strindex(char s[], char t[])
{
    int i, j, k;

    for (i = 0; s[i] != '\0'; i++) {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0')
            return i;
    }
    return -1;
}


/* search_for_pattern */
int
search_for_pattern(void)
{
    char line[MAXLINE];
    int found = 0;

    while (cpl_getline_v2(line, MAXLINE) > 0) {
        if (strindex(line, pattern) >= 0) {
            printf("%s", line);
            found++;
        }
    }
    return found;

}

/* atof_v1: convert string s to double */
double
atof_v1(char s[])
{
    double val, power;
    int i, sign;

    for (i = 0; isspace(s[i]); i++)     /* skip white space */
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10;
    }
    return sign * val / power;
}

/* atoi_v4: convert string s to integer using atof_v1 */
int
atoi_v4(char s[])
{
    return (int) atof_v1(s);
}

/* double_calculator */
void
double_calculator(void)
{
    double sum;
    char line[MAXLINE];

    sum = 0;
    while (cpl_getline_v2(line, MAXLINE) > 0)
        printf("\t%g\n", sum += atof_v1(line));
}

/* int_calculator */
void
int_calculator(void)
{
    int sum;
    char line[MAXLINE];

    sum = 0;
    while (cpl_getline_v2(line, MAXLINE) > 0)
        printf("\t%d\n", sum += atoi_v4(line));
}

/* push: push f onto value stack */
void
push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double
pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

/* getop: get next operator or numeric operand */
int
getop(char s[])
{
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.')
        return c;   /* not a number */
    i = 0;
    if (isdigit(c)) /* collect integer part */
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')   /* collect fraction part */
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}

/* getch */
int
getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* ungetch: push character back on input */
void
ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

/* reverse_polish_calculator */
void
reverse_polish_calculator(void)
{
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof_v1(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
            else
                printf("error: zero divisor\n");
            break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }
}

/* printd: print n in decimal */
void
printd(int n)
{
    if (n < 0) {
        putchar('-');
        n = -n;
    }
    if (n / 10)
        printd(n / 10);
    putchar(n % 10 + '0');
}

/* qsort_v1: sort v[left] ... v[right] into increasing order */
void
qsort_v1(int v[], int left, int right)
{
    int i, last;

    if (left >= right) /* do nothing if array contains fewer than 2 elements. */
        return;
    swap(v, left, (left + right) / 2); /* move partition element */
    last = left;
    for (i = left+1; i <= right; i++)
        if (v[i] < v[left])
            swap(v, ++last, i);
    swap(v, left, last);
    qsort_v1(v, left, last-1);
    qsort_v1(v, last+1, right);
}

/* swap: intercahnge v[i] and v[j] */
void
swap(int v[], int i, int j)
{
    int temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* array_length */
long
array_length(void *v)
{
    return sizeof *v;
}
