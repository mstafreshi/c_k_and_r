#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h> /* for atof() function */
#include "ch2.h"    /* for isleap function */
#include "ch4.h"
#include "ch5.h"

static char allocbuf[ALLOCSIZE];    /* storage for alloc */
static char *allocp = allocbuf;     /* next free position */

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

void
swap_v2(int *x, int *y)
{
    int temp;

    temp = *x;
    *x = *y;
    *y = temp;
}

/* getint: get next integer from input into *pn */
int
getint(int *pn)
{
    int c, sign;

    while (isspace(c = getch()))    /* skip white space */
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);      /* it is not a number */
        return 0;
    }

    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
        c = getch();
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
}

void
print_int_array(int v[], int n)
{
    if (n < 0)
        return;

    putchar('[');
    for (int i = 0; i < n; i++)
        printf("%d%c", v[i], i == n - 1 ? ']' : ' ');
    putchar('\n');
}

int
strlen_v1(char *s)
{
    int n;

    for (n = 0; *s != '\0'; s++, n++)
        ;
    return n;
}

char *
alloc(int n)    /* return pointer to n characters */
{
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp -n;   /* old allocp */
    } else      /* not enough room */
        return 0;
}

char *
afree(char *p)    /* free storage pointed to by p */
{
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
}

/* strcpy_v1: copy t to s; array subscript version */
void
strcpy_v1(char *s, char *t)
{
    int i;

    i = 0;
    while ((s[i] = t[i]) != '\0')
        i++;
}

/* strcpy_v2: copy t to s; pointer version 2 */
void
strcpy_v2(char *s, char *t)
{
    while ((*s++ = *t++) != '\0')
        ; 
}

/* strcpy_v3: copy t to s; pointer version 3 */
void
strcpy_v3(char *s, char *t)
{
    while (*s++ = *t++)
        ;
}

/* strcmp_v1: return <0 if s<t, 0 if s==t, >0 if s>t */
int
strcmp_v1(char *s, char *t)
{
    int i;

    for (i = 0; s[i] == t[i]; i++)
        if (s[i] == '\0')
            return 0;
    return s[i] - t[i];
}

/* strcmp_v2: return <0 if s<t, 0 if s==t, >0 if s>t */
int
strcmp_v2(char *s, char *t)
{
    for ( ; *s == *t; s++, t++)
        if (*s == '\0')
            return 0;
    return *s - *t;
}

/* readlines: read input lines */
int
readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = cpl_getline_v2(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len - 1] = '\0';   /* delete new line */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    return nlines;
}

/* writelines: write output lines */
void
writelines(char *lineptr[], int nlines)
{
    int i;

    for (i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

/* qsort_v2: sort v[left]...v[right] into increasing order */
void
qsort_v2(char *v[], int left, int right)
{
    int i, last;

    if (left >= right)
        return;

    swap_v3(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap_v3(v, ++last, i);

    swap_v3(v, left, last);
    qsort_v2(v, left, last - 1);
    qsort_v2(v, last + 1, right);
}

/* swap_v3: interchange v[i] and v[j] */
void
swap_v3(char *v[], int i, int j)
{
    char *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* sort_lines */
void
sort_lines(void)
{
    int nlines;     /* number of input lines read */
    char *lineptr[MAXLINES];    /* pointers to text lines */

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort_v2(lineptr, 0, nlines  - 1);
        writelines(lineptr, nlines);
    } else {
        printf("error: input too big to sort\n");
    }
}

/* day of year: set day of year from month & day */
int
day_of_year(int year, int month, int day)
{
    int i, leap;

    leap = isleap(year);
    for (i = 1; i < month; i++)
        day += daytab[leap][i];
    return day;
}

/* month_day: set month, day from day of year */
void
month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;

    leap = isleap(year);
    for (i = 1; yearday > daytab[leap][i]; i++)
        yearday -= daytab[leap][i];
    *pmonth = i;
    *pday = yearday;
}

/* month_name: return name of n-th month */
char *
month_name(int n)
{
    static char *name[] = {
        "Illegal month",
        "January", "February", "March",
        "April", "May", "june",
        "July", "Auguest", "September",
        "October", "November", "December"
    };

    return (n < 1 || n > 12) ? name[0] : name[n];
}

/* print_command_line_arguments_v1 */
void
print_command_line_arguments_v1(int argc, char *argv[])
{
    int i;

    for (i = 1; i < argc; i++)
        printf("%s%s", argv[i], (i < argc - 1) ? " " : "");
    printf("\n");
}

/* print_command_line_arguments_v2 */
void
print_command_line_arguments_v2(int argc, char *argv[])
{
    while (--argc > 0)
        printf("%s%s", *++argv, (argc > 1) ? " " : "");
   printf("\n"); 
}

/* print_command_line_arguments_v3 */
void
print_command_line_arguments_v3(int argc, char *argv[])
{
    while (--argc > 0)
        /* the format argument of printf() can be an expression too */
        printf((argc > 1) ? "%s " : "%s", *++argv);
    printf("\n");
}

/* search_for_pattern_v2 */
int
search_for_pattern_v2(int argc, char *argv[])
{
    char line[MAXLINE];
    int found = 0;

    if (argc != 2)
        printf("Usage: %s pattern\n", *argv);
    else
        while (cpl_getline_v2(line, MAXLINE) > 0)
            if (strstr(line, argv[1]) != NULL) {
                printf("%s", line);
                found++;
            }
    return found;
}

/* find_v1 */
int
find_v1(int argc, char *argv[])
{
    char line[MAXLINE];
    long lineno = 0;
    long c, except = 0, number = 0, found = 0;
    char *program_name = argv[0];

    while (--argc > 0 && (*++argv)[0] == '-')
        while (c = *++argv[0])
            switch (c) {
            case 'x':
                except = 1;
                break;
            case 'n':
                number = 1;
                break;
            default:
                printf("%s: illegal option %c\n", program_name, (int) c);
                argc = 0;
                found = -1;
                break;
            }
    if (argc != 1)
        printf("Usage: %s -x -n pattern\n", program_name);
    else
        while (cpl_getline_v2(line, MAXLINE) > 0) {
            lineno++;
            if ((strstr(line, *argv) != NULL) != except) {
                if (number)
                    printf("%ld:", lineno);
                printf("%s", line);
                found++;
            }
        }
    return found;
}

/* sort_input_lines */
int
sort_input_lines(int argc, char *argv[])
{
    int nlines;         /* number of input lines read */
    int numeric = 0;    /* 1 if numeric sort */
    char *lineptr[MAXLINES];

    if (argc > 1 && strcmp(argv[1], "-n") == 0)
        numeric = 1;
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort_v3((void **) lineptr, 0, nlines - 1,
            (int (*)(void *, void *))(numeric ? numcmp : strcmp));
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

/* qsort_v3: sort v[left]...v[right] into increasing order */
void
qsort_v3(void *v[], int left, int right, int (*comp)(void *, void *))
{
    int i, last;

    if (left >= right)      /* do nothing if array contains */
        return;             /* fewer than two elements */
    swap_v4(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0)
            swap_v4(v, ++last, i);
    swap_v4(v, left, last);
    qsort_v3(v, left, last - 1, comp);
    qsort_v3(v, last + 1, right, comp);
}

/* swap_v4 */
void
swap_v4(void *v[], int i, int j)
{
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* numcmp: compare s1 and s2 numerically */
int
numcmp(const char *s1, const char *s2)
{
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;    
}
