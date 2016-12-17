#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../ll/util.h"
#include "../ll/ll.h"
#include "../qlib.h"
#include "treelib.h"

/*
 * I recently encountered with a question in an interview at e-commerce company. The interviewer asked the following question:
 * There is BST given with root node with key part as integer only. The structure of each node is as follows:
 */
    void
range_get (node_td *node, int *minr, int *maxr, int match)
{
    if (!node) return;
    
    range_get(node->left, minr, maxr, match);

    if (node->i < match) {
        if (*minr == -1) {
            *minr = node->i;
        } else if (*minr < node->i) {
            *minr = node->i;
        }
    } else if (node->i > match) {
        if (*maxr == -1) {
            *maxr = node->i;
        } else if (*maxr > node->i) {
            *maxr = node->i;
        }
    } else {
        *minr = node->left ? node->left->i : *minr;
        *maxr = node->right ? node->right->i : *maxr;
        return;
    }
    
    range_get(node->right, minr, maxr, match);
}

    int
main (int argc, char *argv[])
{
    int *a, minr, maxr;
    node_td *root;
    
   a = get_from_main(argc, argv);
   root = cons_tree_ln(a);
   print_tr(root, "main");

   minr = maxr = -1;
   range_get(root, &minr, &maxr, 80);
   printf("Range is %d %d \n", minr, maxr);
}

