#ifndef _CH2_H
#define _CH2_H

// ُTODO: bit operators is not done yet.

int isleap(int year);
void ascii_table(void);

int atoi_v1(char s[]);
int atoi_v2(char s[]);

/*
int (*atoi)(char s[]) = atoi_v1;
*/

int lower(int c);

void squeeze(char s[], int c);
void cpl_strcat(char s[], char t[]);

int bitcount(unsigned x);

#endif
