#include <stdlib.h>
#include "getword.h"

#define MAXNODES 1000

/* binary tree of words in input */
struct tnode
{
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int build_node_list(struct tnode *, struct tnode *[]);
void sort_node_list(struct tnode *[], int);
int getword(char *, int);

struct tnode *node_list[MAXNODES]; /* pointers to nodes in tree */

/*
    output list of distinct words in input sorted into decreasing order of
    frequency of occurrence preceded by word count.
 */
int main(int argc, char *argv[])
{
    char word[MAXWORD];
    struct tnode *root = NULL;
    while (getword(word, MAXWORD) != EOF)
    {
        if (isalpha(word[0]))
        {
            root = addtree(root, word);
        }
    }

    int node_count = build_node_list(root, node_list);
    sort_node_list(node_list, node_count);

    for (int i = 0; i < node_count; i++)
    {
        struct tnode *node = node_list[i];
        printf("%d %s\n", node->count, node->word);
    }
    return 0;
}

/*
    build_node_list: fill node_list with pointers to all nodes in
    tree p. Return count of nodes in node_list
 */
int build_node_list(struct tnode *p, struct tnode *node_list[])
{
    static int node_count = 0;
    if (p != NULL)
    {
        build_node_list(p->left, node_list);
        if (node_count < MAXNODES)
        {
            node_list[node_count++] = p;
        }
        build_node_list(p->right, node_list);
    }
    return node_count;
}

void swap(struct tnode *v[], int i, int j);

/*
    sort_node_list: sort node_list into descending order of
    node count
 */
void sort_node_list(struct tnode *node_list[], int node_count)
{
    for (int gap = node_count / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < node_count; i++)
        {
            for (int j = i - gap; j >= 0; j -= gap)
            {
                if ((node_list[j]->count) >= (node_list[j + gap]->count))
                {
                    break;
                }
                swap(node_list, j, j + gap);
            }
        }
    }
}

/* swap: interchange v[i] and v[j] */
void swap(struct tnode *v[], int i, int j)
{
    struct tnode *tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
}

struct tnode *talloc(void);
struct lnode *listalloc(void);

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
    if (p == NULL) /* new word -> add new node */
    {
        p = talloc();
        p->word = strdup(w);
        p->left = p->right = NULL;
        p->count = 1;
    }
    else
    {
        int cond = strcmp(w, p->word);
        if (cond == 0)
        {
            ++p->count;
        }
        else if (cond < 0)
        {
            /* less -> add to left subtree */
            p->left = addtree(p->left, w);
        }
        else
        {
            /* greater -> add to right subtree */
            p->right = addtree(p->right, w);
        }
    }
    return p;
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