#ifndef _CH4_H
#define _CH4_H

#define MAXLINE     1000    /* maximum input line length */
#define MAXVAL      100     /* maximum depth of val stack */
#define BUFSIZE     100
#define MAXOP       100     /* max size of operand or operator */
#define NUMBER      '0'     /* signal that a number was found */

int cpl_getline_v2(char line[], int max);
int strindex(char source[], char searchfor[]);
int search_for_pattern(void);
double atof_v1(char s[]);
int atoi_v4(char s[]);
void double_calculator(void);
void int_calculator(void);
void push(double f);
double pop(void);
int getch(void);
void ungetch(int);
int getop(char s[]);
void reverse_polish_calculator(void);
void printd(int n);
void qsort_v1(int v[], int left, int right);
void swap(int v[], int i, int j);
long array_length(void *v);

#endif
