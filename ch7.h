#ifndef _CH7_H
#define _CH7_H

int tolower_v1(void);
void print_string_formats(void);
void minprintf(char *fmt, ...);
void minprintf_test(void);
void rudimentary_calculator(void);
int read_date(char *date, int *day, char *month, int *year);
void read_date_test(char *program_name, char *date);
int filecopy(FILE *ifp, FILE *ofp);
int cat_v1(int argc, char *argv[]);

#endif