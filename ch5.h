#ifndef _CH5_H
#define _CH5_H

#define ALLOCSIZE   10000   /* size of available space */
#define MAXLINES    5000    /* max #lines to be sorted */
#define MAXLEN      1000    /* maximum length of any input line */

#define MAXTOKEN    1000
enum { NAME, PARENS, BRACKETS };

void swap_v2(int *px, int *py);
int getint(int *pn);
void print_int_array(int v[], int n);
int strlen_v1(char *s);
char *alloc(int n);
char *afree(char *p);
void strcpy_v1(char *s, char *t);
void strcpy_v2(char *s, char *t);
void strcpy_v3(char *s, char *t);
int strcmp_v1(char *s, char *t);
int strcmp_v2(char *s, char *t);
int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int maxlines);
void qsort_v2(char *v[], int left, int right);
void swap_v3(char *v[], int i, int j);

// int (*getint2)(int *);
void sort_lines(void);
int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);
char *month_name(int n);
void print_command_line_arguments_v1(int argc, char *argv[]);
void print_command_line_arguments_v2(int argc, char *argv[]);
void print_command_line_arguments_v3(int argc, char *argv[]);
int search_for_pattern_v2(int argc, char *argv[]);
int find_v1(int argc, char *argv[]);

int sort_input_lines(int argc, char *argv[]);
void qsort_v3(void *v[], int left, int right, int (*comp)(void *, void *));
void swap_v4(void *v[], int i, int j);
int numcmp(const char *s1, const char *s2);

void dcl(void);
void dirdcl(void);
int gettoken(void);
int undcl(void);
void complicated_declarations(void);

#endif
