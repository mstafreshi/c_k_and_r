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
void check_errors_test(void);
char *fgets_v1(char *s, int n, FILE *iop);
int fputs_v1(char *s, FILE *iop);
int getline_v3(char *line, int max);

#endif