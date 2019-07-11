#include <stdlib.h>
#include <string.h>

/* table entry */
struct nlist
{
    struct nlist *next;
    char *name; /* defined name */
    char *defn; /* replacement text */
};

struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);
void undef(char *name);