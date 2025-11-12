#ifndef _CH6_H
#define _CH6_H

#define MAXWORD     100

struct key {
    char *word;
    int count;
};

int binsearch_v2(char *word, struct key *tab, int);
int getword(char *word, int lim);
void count_c_language_keywords_v1(void);
void count_c_language_keywords_v2(void);

#endif
