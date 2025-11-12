#ifndef _CH6_H
#define _CH6_H

#define MAXWORD     100
#define IN          1
#define HASHSIZE    101

struct key {
    char *word;
    int count;
};

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

int binsearch_v2(char *word, struct key *tab, int);
int getword(char *word, int lim);
void count_c_language_keywords_v1(void);
void count_c_language_keywords_v2(void);
struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
char *strdup_v1(char *s);
struct tnode *talloc(void);
unsigned hash(char *s);
struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);

#endif
