#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../ll/util.h"
#include "../ll/ll.h"
#include "../qlib.h"
#include "treelib.h"

int
inorder_next (node_td *node, node_td **inon, int nos)
{
    int rv;

    if (!node) return 0;

    rv = inorder_next(node->left, inon, nos);
    if (rv) return rv;

    if (node->i == nos) {
        printf(" tos %d %p %p\n", nos, node->left, node->right);
        if (node->right) {
            *inon = node->right;
            return 1;
        } else {
            *inon = node;
            return 0;
        }
    }

    if (*inon) {
            printf(" L tos node right %d %p %p\n", nos, node->left, node->right);
        if (node->left == *inon) {
            *inon = node;
            return 1;
        } else if (node->right == *inon) {
            printf(" tos node right %d %p %p\n", nos, node->left, node->right);
            return 0; 
        } else {
            printf(" at %d %d \n", (*inon)->i, node->i);
            *inon = node;
            return 1;
        }
    }
    
    rv = inorder_next(node->right, inon, nos);
    if (rv) return rv;
    
    if (*inon) {
            printf(" R tos node right %d %p %p\n", nos, node->left, node->right);
        if (node->left == *inon) {
            *inon = node;
            return 1;
        } else if (node->right == *inon) {
            printf(" tos node right %d %p %p\n", nos, node->left, node->right);
            return 0; 
        } else {
            printf(" at %d %d \n", (*inon)->i, node->i);
            *inon = node;
            return 1;
        }
    }
    return 0;
}


int
main (int argc, char *argv[])
{
    int *a, nos = 4, i;
    node_td *root, *prev, *node, *ntof = NULL;

    a = get_from_main(argc, argv);
    root = cons_tree_ln(a);
    print_tr(root, "main");
    getchar();

    if (root && root->i == nos) {
        node = root->right;
        while (node) {
            prev = node;
            node = node->left;
        }
        printf("Inorder next for this root node is  %d\n", prev->i);    
        return 1;
    }

    i = 1;
    while (a[i] != INVALID) {
        node = inorder_next(root, &ntof, a[i]);
        printf("Inorder next for %d %d\n", a[i], ntof ? ntof->i : -1);     
        i++;
        ntof = NULL;
        getchar();
    }
}

