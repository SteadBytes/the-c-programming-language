#include "lookup.h"

#define HASHSIZE 101

static struct nlist *hashtab[HASHSIZE]; /* pointer table */

/* hash: form hash value for string s */
unsigned hash(char *s)
{
    unsigned hashval;
    /* add each char value in s to scrambled combination of previous ones */
    for (hashval = 0; *s != '\0'; s++)
    {
        hashval = *s + 31 * hashval;
    }
    return hashval % HASHSIZE;
}

struct nlist *lookup(char *s)
{
    for (struct nlist *np = hashtab[hash(s)]; np != NULL; np = np->next)
    {
        if (strcmp(s, np->name) == 0)
        {
            return np;
        }
        return NULL;
    }
}

/* install: put (name, defn) in lookup table */
struct nlist *install(char *name, char *defn)
{
    struct nlist *np = lookup(name);
    if (np == NULL)
    {
        np = (struct nlist *)malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
        {
            return NULL;
        }
        unsigned hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    }
    else
    {
        free((void *)np->defn);
    }
    if ((np->defn = strdup(defn)) == NULL)
    {
        return NULL;
    }
    return np;
}

/* undef: remove name and definition from lookup table */
void undef(char *name)
{
    unsigned h = hash(name);
    struct nlist *prevp, *np;
    for (np = hashtab[h]; np != NULL; np = np->next)
    {
        if (strcmp(name, np->name) == 0)
        {
            break;
        }
        prevp = np;
    }
    if (np != NULL)
    {
        if (prevp == NULL)
        {
            /* first entry in hash list */
            hashtab[h] = np->next;
        }
        else
        {
            /* within hash list -> remove from pointer chain */
            prevp->next = np->next;
        }
        free_nlist(np);
    }
}

/* free_nlist: free allocated nlist structure */
void free_nlist(struct nlist *np)
{
    free((void *)np->name);
    free((void *)np->defn);
    free((void *)np);
}
