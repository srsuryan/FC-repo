#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../ll/util.h"
#include "../ll/ll.h"
#include "../qlib.h"
#include "treelib.h"

typedef struct lbst_ {
    int max;
    node_td *ptr;
} lbst_td;

lbst_td lbst = {0};

int debug = 1;
int
largest_bst (node_td *node, int *c)
{
    int rv1, rv2;

    if (!node) {
#if 0
        (*c)++;
        if (lbst.max < *c) {
            lbst.max = *c;
            lbst.ptr = node;
        }
#endif
        return TRUE;
    }

    rv1 = largest_bst(node->left, c);
    rv2 = largest_bst(node->right, c);

    if (rv1 && rv2) {
        if (node->left) {
            if (node->i < node->left->i) {
                *c = 0;
                return FALSE;
            }
        }

        if (node->right) {
            if (node->i > node->right->i) {
                *c = 0;
                return FALSE;
            }
        }

        *c += 1;
        if (lbst.max < *c) {
            lbst.max = *c;
            lbst.ptr = node;
            if (1) {
                printf("Node max at %d %d\n", node->i, *c);
            }
        }
 
        return TRUE;
    } else {
        return FALSE;
    }
}

int
main (int argc, char *argv[])
{
    int *a, c = 0;
    node_td *root, *prev, *node;

    a = get_from_main(argc, argv);
    root = cons_tree_ln(a);
    print_tr(root, "main");
    getchar();
    largest_bst(root, &c);
    printf("Largest bst is at node %d count %d\n", lbst.ptr ? lbst.ptr->i : -1, lbst.max);
}
