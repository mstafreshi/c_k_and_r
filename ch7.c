#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdarg.h>

#include "ch7.h"

/* tolower_v1: convert stdin input to lowercase */
int
tolower_v1(void)
{
    int c, n;
    
    n = 0;
    while ((c = getchar()) != EOF) {
        putchar(tolower(c));
        n++;
    }
    return n;
}

/* print_string_formats */
void
print_string_formats()
{
    char s[] = "hello, world";
    
    printf("<%%s>      : <%s>\n", s);
    printf("<%%10s>    : <%10s>\n", s);
    printf("<%%.10s>   : <%.10s>\n", s);
    printf("<%%-10s>   : <%-10s>\n", s);
    printf("<%%.15s>   : <%.15s>\n", s);
    printf("<%%-15s>   : <%-15s>\n", s);
    printf("<%%15.10s> : <%15.10s>\n", s);
    printf("<%%-15.10s>: <%-15.10s>\n", s);
}

/* minprintf: minimal printf with variable argument list */
void
minprintf(char *fmt, ...)
{
    va_list ap;     /* points to each unnamed arg in turn */
    char *p, *sval;
    int ival;
    double dval;
    
    va_start(ap, fmt);
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        
        switch (*++p) {
        case 'd':
            ival = va_arg(ap, int);
            printf("%d", ival);
            break;
        case 'f':
            dval = va_arg(ap, double);
            printf("%f", dval);
            break;
        case 's':
            for (sval = va_arg(ap, char *); *sval; sval++)
                putchar(*sval);
            break;
        default:
            putchar(*p);
            break;
        }
    }
    va_end(ap);     /* clean up when done */
}

/* minprintf_test */
void
minprintf_test(void)
{
    minprintf(
        "name: <%s>\nage: <%d>\ngrade: <%f>\nunknown format:<%p>\n",
        "Mohsen safari", 42, 12.65, "blah blah"
    );
}

/* rudimentary_calculator */
void
rudimentary_calculator(void)
{
    double sum , v;
    
    sum = 0;
    while (scanf("%lf", &v) == 1)
        printf("\t%.2f\n", sum += v);
}

/* read_date: read date in format: 25 Dec 1998 */
int
read_date(char *date, int  *day, char *month, int *year)
{
    return sscanf(date, "%d %s %d", day, month, year);
}

/* read_date_test */
void
read_date_test(char *program_name, char *date)
{
    int n, day, year;
    char month[4];
    
    n = read_date(date, &day, month, &year);
    if (n != 3) {
        fprintf(stderr, "usage: %s [25 Dec 1988]\n", program_name);
        exit(1);
    }
    
    printf("n=%d day=%d month=%s year=%d\n", n, day, month, year);
}

/* filecopy: copy file ifp to file ofp */
int
filecopy(FILE *ifp, FILE *ofp)
{
    int c, n;
    
    n = 0;
    while ((c = getc(ifp)) != EOF) {
        putc(c, ofp);
        n++;
    }
    return n;
}

/* cat_v1 */
int
cat_v1(int argc, char *argv[])
{
    FILE *fp;
    int n = 0;          /* number of characters printed */
    
    if (argc == 1)      /* no args; copy standard input */
        n = filecopy(stdin, stdout);
    else
        while (--argc > 0) {
            if ((fp = fopen(*++argv, "r")) == NULL) {
                printf("cat: can't open %s\n", *argv);
                exit(1);
            } else {
                n += filecopy(fp, stdout);
                fclose(fp);
            }
        }
    return n;
}