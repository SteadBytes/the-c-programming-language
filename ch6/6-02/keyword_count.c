#include <stdlib.h>
#include "getword_c.h"

#define DEFAULT_COMPARISON_LEN 6

struct tnode
{
    char *word;
    int matched;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *, int, int *);
void treeprint(struct tnode *);
int getword_c(char *, int);

/*
    output each group of variable names where the first n chars match
    in alphabetical order (default n=6)
    options:
    -n[int]
 */
int main(int argc, char *argv[])
{
    int n = (argc == 2 && (*++argv)[0] == '-' && *(argv[0] + 1) == 'n') ? atoi(argv[0] + 2) : DEFAULT_COMPARISON_LEN;

    char word[MAXWORD];
    struct tnode *root = NULL;
    while (getword_c(word, MAXWORD) != EOF)
    {
        int matched = 0; /* 1 if matching name found else 0 */
        if (isalpha(word[0]) && strlen(word) >= n)
        {
            /*
                recursive calls will update matched to determine matched status
                of new nodes created
            */
            root = addtree(root, word, n, &matched);
        }
    }
    treeprint(root);
    return 0;
}

struct tnode *talloc(void);

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w, int n, int *matched)
{
    if (p == NULL) /* new word -> add new node */
    {
        p = talloc();
        p->word = strdup(w);
        p->matched = *matched;
        p->left = p->right = NULL;
    }
    else
    {
        int cond = strncmp(w, p->word, n);
        if (cond == 0) /* first n chars match */
        {
            *matched = 1; /* nodes in this subtree will be matched */
            p->matched = 1;
        }
        else if (cond < 0)
        {
            /* less -> add to left subtree */
            p->left = addtree(p->left, w, n, matched);
        }
        else
        {
            /* greater -> add to right subtree */
            p->right = addtree(p->right, w, n, matched);
        }
    }
    return p;
}

/* treeprint: in-order output of all nodes in tree p that have been matched */
void treeprint(struct tnode *p)
{
    if (p != NULL)
    {
        treeprint(p->left);
        if (p->matched == 1)
        {
            puts(p->word);
        }
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