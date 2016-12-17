#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../ll/util.h"
#include "../ll/ll.h"
#include "../qlib.h"
#include "treelib.h"

node_td **lnode;

node_td *
make_th (node_td *node, int *c)
{
    node_td *tnode;

    if (!node) return NULL;

    tnode = make_th(node->left, c);
    
    if (tnode) {
        tnode->right = node;
    }

    tnode = make_th(node->right, c);

    if (tnode) {
        if (node->right != tnode) {
            tnode->right = node;
        } else {
            return tnode;
        }
    }

    if (!node->right) {
        lnode[(*c)] = node;
        (*c)++;
        return node;
    }

    return NULL;
}

void
inorder_cnt (node_td *node, int *c)
{
    if (!node) return;

    inorder_cnt(node->left, c);
    (*c)++;
    inorder_cnt(node->right, c);
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

    inorder_cnt(root, &c);
    if (debug) {
        printf("Total nodes %d\n",c);
    }
    
    lnode = (node_td *)calloc(1, sizeof(int *)*c);

    c = 0;
    make_th(root, &c);

    node = root;
    while (node) {
        prev = node;
        node = node->left;
    }

    node = prev;
    while (node) {
        printf("node %d ", node->i);
        node = node->right;
    }
    printf("\n");

    c = 0;
    while (lnode[c]) {
        lnode[c]->right = NULL;
        c++;
    }
}

