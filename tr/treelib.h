#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../qlib.h"

#if 0
typedef struct node_td_ {
    int i;
    struct node_td_ *left;
    struct node_td_ *right;
} node_td;
#endif

#define DUMMY 0xDEADBEEF
void
inorder (node_td *node);

void
instert_val (node_td *node, int i, node_td *prev);

node_td *
cons_tree (int a[]);

void
print_tr (node_td *node, char *str);

node_td *cons_tree_ln (int *a);
