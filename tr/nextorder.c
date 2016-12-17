#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../ll/util.h"
#include "treelib.h"
#include "../qlib.h"

#if 0
typedef struct node_td_ {
    int i;
    struct node_td_ *left;
    struct node_td_ *right;
} node_td;
#endif

node_td *nextn = NULL;

node_td *
get_lmost (node_td *node)
{
    node_td *prev;

    if (!node) return NULL;

    prev = node;
    while (node) {
        prev = node;
        node = node->left;
    }

    return prev;
}

int
next_node_find (node_td *node, node_td *ntos)
{
    int rv = 0;

    if (!node) return FALSE;

    rv = next_node_find(node->left, ntos);
    if (rv) {
        if (!nextn) {
            nextn = node;
            return 1;
        } 
    }

    if (ntos == node) {
        printf("Look for next for %d \n", node->i);
        nextn = get_lmost(ntos->right);
        return 1;        
    }

    rv = next_node_find(node->right, ntos);
    return rv;
}

void
inorder (node_td *node) 
{
    if (!node) return;

    inorder(node->left);
    printf("Node %d\n", node->i);
    inorder(node->right);
}

node_td *
get_tree_nodes (int c, node_td *node)
{
    node_td *rn;

      if (!node) return NULL;
      
      if (c == node->i) {
          return node;
      }
      
      rn = get_tree_nodes(c, node->left);
      if (rn) return rn;

      rn = get_tree_nodes(c, node->right);
      if (rn) return rn;
     
      return NULL;
}

int
main (int argc, char *argv[])
{
    int i, *a, minr, maxr, c = 0;
    node_td *root, *b[32] = {0};

    a = get_from_main(argc, argv);
    root = cons_tree_ln(a);
    inorder(root);

    i = 0;
    while (a[i] != INVALID) {
        b[i] = get_tree_nodes(a[i], root);
        printf("b[%d] = %d\n", i, b[i]->i);
        i++;
    }

    i = 0;
    while (a[i] != INVALID) {
        printf("for %d b %d\n", a[i], b[i]->i);
        next_node_find(root, b[i]);
        printf("Next node val for %d is %d \n", a[i], nextn ? nextn->i : -1 );
        nextn = NULL;
        i++;
        getchar();
    }
    inorder(root);
}
