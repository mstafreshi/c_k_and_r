#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "ch4.h"
#include "ch6.h"

struct key keytab[] = {
    "auto", 0,
    "break", 0,
    "case", 0,
    "char", 0,
    "const", 0,
    "continue", 0,
    "default", 0,
    "do", 0,
    "double", 0,
    "else", 0,
    "enum", 0,
    "extern", 0,
    "float", 0,
    "for", 0,
    "goto", 0,
    "if", 0,
    "int", 0,
    "long", 0,
    "register", 0,
    "return", 0,
    "short", 0,
    "signed", 0,
    "sizeof", 0,
    "static", 0,
    "struct", 0,
    "switch", 0,
    "typedef", 0,
    "union", 0,
    "unsigned", 0,
    "void", 0,
    "volatile", 0,
    "while", 0
};

static struct nlist *hashtab[HASHSIZE];     /* pointer table */

/* binsearch_v2: find word in tab[0]...tab[n-1] */
int
binsearch_v2(char *word, struct key tab[], int n)
{
    int cond;
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

/* getword: get next word or character from input */
int
getword(char *word, int limit)
{
    int c;
    char *w = word;

    while (isspace(c = getch()))
        ;
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for ( ; --limit > 0; w++)
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
        *w = '\0';
    return word[0];    

}

/* count_c_language_keywords */
void
count_c_language_keywords_v1(void)
{
    int n, nkeys;
    char word[MAXWORD];

    nkeys = sizeof(keytab) / sizeof(keytab[0]);
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            if ((n = binsearch_v2(word, keytab, nkeys)) >= 0)
                keytab[n].count++;
    for (n = 0; n < nkeys; n++)
        if (keytab[n].count > 0)
            printf("%4d %s\n",
                keytab[n].count, keytab[n].word);
}

/* binsearch_v3: find word in tab[0]...tab[n-1] */
struct key *
binsearch_v3(char *word, struct key *tab, int n)
{
    int cond;
    struct key *low = &tab[0];
    struct key *high = &tab[n];
    struct key *mid;

    while (low < high) {
        mid = low + (high - low) / 2;
        if ((cond = strcmp(word, mid->word)) < 0)
            high = mid;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return NULL;
}

/* count_c_language_keywords_v2 */
void
count_c_language_keywords_v2(void)
{
    char word[MAXWORD];
    struct key *p;
    int nkeys;

    nkeys = sizeof(keytab) / sizeof(keytab[0]);
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            if ((p = binsearch_v3(word, keytab, nkeys)) != NULL)
                p->count++;
    for (p = keytab; p < keytab + nkeys; p++)
        if (p->count > 0)
            printf("%4d %s\n", p->count, p->word);
}

/* addtree: add a node with w, at or below p */
struct tnode *
addtree(struct tnode *p, char *w)
{
    int cond;

    if (p == NULL) {        /* a new word has arrived */
        p = talloc();       /* make a new node */
        p->word = strdup_v1(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0)
        p->count++;         /* repeated word */
    else if (cond < 0)      /* less than into left subtree */
        p->left = addtree(p->left, w);
    else                    /* greater than into right subtree */
        p->right = addtree(p->right, w);
    return p;
}

/* treeprint: in-order print of tree p */
void
treeprint(struct tnode *p)
{
    if (p != NULL) {
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}

/* talloc: make a tnode */
struct tnode *
talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

/* strdup_v1: make a duuplicate of s */
char *
strdup_v1(char *s)
{
    char *p;

    p = (char *) malloc(strlen(s) + 1);     /* +1 for '\0' */
    if (p != NULL)
        strcpy(p, s);
    return p;
}

/* hash: form hash value for string s */
unsigned
hash(char *s)
{
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *
lookup(char *s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;      /* found */
    return NULL;            /* not found */
}

/* install: put (name, defn) in hashtab */
struct nlist *
install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {      /* not found */
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup_v1(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else      /* already there */
        free((void *) np->defn);    /* free previous defn */
    if ((np->defn = strdup_v1(defn)) == NULL)
        return NULL;
    return np;
}
