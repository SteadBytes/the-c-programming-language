#include <stdlib.h>
#include "getword.h"

#define DEFAULT_COMPARISON_LEN 6

/* linked list of line numbers */
struct lnode
{
    int line_n;
    struct lnode *next;
};

/* binary tree of words in input */
struct tnode
{
    char *word;
    struct lnode *lines; /* linked list of line numbers where word occurred */
    struct tnode *left;
    struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *, int);
void treeprint(struct tnode *);
int getword(char *, int);
int isnoise(char *);
/*
    output list of all unique words in input with a list of line numbers on which
    each word occurs. Noise words are ignored ('and', 'the' e.t.c.)
 */
int main(int argc, char *argv[])
{
    char word[MAXWORD];
    struct tnode *root = NULL;
    int line_n = 1;
    while (getword(word, MAXWORD) != EOF)
    {

        /* track occurrences of non-noise words only */
        if (isalpha(word[0]) && !isnoise(word))
        {
            root = addtree(root, word, line_n);
        }
        else if (word[0] == '\n')
        {
            line_n++;
        }
    }
    treeprint(root);
    return 0;
}

/* isnoise: return 1 if w is a 'noise word' else 0 */
int isnoise(char *w)
{
    static char *noise_words[] = {
        "a",
        "an",
        "and",
        "is",
        "of",
        "or",
        "that"
        "the",
        "this"};

    int low = 0, high = sizeof(noise_words) / sizeof(char *) - 1;
    /* binary search for w in noise_words */
    while (low <= high)
    {
        int mid = (low + high) / 2;
        int cond = strcmp(w, noise_words[mid]);
        if (cond <= 0)
        {
            high = mid - 1;
        }
        else if (cond > 0)
        {
            low = mid + 1;
        }
        else
        {
            return 1;
        }
    }
    return 0;
}

struct tnode *talloc(void);
struct lnode *listalloc(void);
void add_line(struct tnode *p, int line_n);

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w, int line_n)
{
    if (p == NULL) /* new word -> add new node */
    {
        p = talloc();
        p->word = strdup(w);
        p->left = p->right = NULL;
        struct lnode *l = listalloc();
        l->line_n = line_n;
        l->next = NULL;
        p->lines = l;
    }
    else
    {
        int cond = strcmp(w, p->word);
        if (cond == 0)
        {
            add_line(p, line_n);
        }
        else if (cond < 0)
        {
            /* less -> add to left subtree */
            p->left = addtree(p->left, w, line_n);
        }
        else
        {
            /* greater -> add to right subtree */
            p->right = addtree(p->right, w, line_n);
        }
    }
    return p;
}

/* add_line: add a new line number to a node */
void add_line(struct tnode *p, int line_n)
{
    struct lnode *l = p->lines;
    /* traverse linked list to find a matching line number */
    while (l->next != NULL && l->line_n != line_n)
    {
        l = l->next;
    }
    /* end of list found -> add new node with this line number */
    if (l->line_n != line_n)
    {
        struct lnode *l2 = listalloc();
        l2->line_n = line_n;
        l2->next = NULL;
        l->next = l2;
    }
}

/*
    treeprint: in-order output of all nodes in tree p along with the line numbers
    the word in each node occurred in input
*/
void treeprint(struct tnode *p)
{
    if (p != NULL)
    {
        treeprint(p->left);
        puts(p->word);
        /* print line numbers for current node */
        for (struct lnode *l = p->lines; l != NULL; l = l->next)
        {
            printf("%d ", l->line_n);
        }
        printf("\n");
        treeprint(p->right);
    }
}

/* talloc: allocate tnode */
struct tnode *talloc(void)
{
    /*
        malloc returns pointer to void -> standard practice
        to explicitly coerce the pointer to desired type w/ a cast
     */
    return (struct tnode *)malloc(sizeof(struct tnode));
}

/* lalloc: allocate lnode */
struct lnode *listalloc(void)
{
    return (struct lnode *)malloc(sizeof(struct lnode));
}