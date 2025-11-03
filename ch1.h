#ifndef _CH1_H
#define _CH1_H

#define LOWER   0
#define UPPER   300
#define STEP    20

#define IN      1   /* inside a word */
#define OUT     0   /* outside a word */

#define MAXLINE 1000    /* maximum input line size */

extern char line[];
extern char longest[];
extern int max;

void fahr_to_celsius_v1(void);
void fahr_to_celsius_v2(void);
void fahr_to_celsius_v3(void);
void fahr_to_celsius_v4(void);

void copy_v1(void);
void copy_v2(void);

void nc_v1(void);
void nc_v2(void);

void nl(void);

void wc(void);

void count_digit_whitespace_other(void);

int power_v1(int base, int n);
int power_v2(int base, int n);

int cpl_getline_v1(char s[], int lim);
void copy(char to[], char from[]);
void print_longest_line(void);
int specialized_cpl_getline(void);
void specialized_copy(void);
void specialized_print_longest_line(void);

#endif
