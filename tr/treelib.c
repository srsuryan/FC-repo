#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../ll/util.h"
#include "treelib.h"

node_td *root = NULL;

int debug;

#if 1
void
inorder (node_td *node)
{
    if (!node) return;
    if (!root) {root = node;}

    inorder(node->left);

    printf(" <<%d %s>>", node->i, (node == root) ? "ROOT" :"");

    inorder(node->right);
}
#endif

void
insert_rtol (int fd, int v1, int v2)
{
    node_td *node, *nl, *nr;
    int val;

    node = (node_td *)qpop(fd);
    if (!node) return;
    
    if ((v1 != INVALID) && (v1 != DUMMY)) {
        nl = calloc(1, sizeof(node_td));
        nl->i = v1;
        node->left = nl;
        qpush(fd, nl);
    } 

    if ((v2 != INVALID) && (v2 != DUMMY)) {
        nr = calloc(1, sizeof(node_td));
        nr->i = v2;
        node->right = nr;
        qpush(fd, nr);
    }
    
    if (debug) {
        printf(" node %d v1 %d v2 %d\n", node->i, v1, v2);
    }
}

node_td *
cons_tree_ln (int *a)
{
    node_td *root;
    int i = 0, fd, rv;
    queue_td *q;

    debug = 0;
    rv = lib_init(QUEUE, &q, &fd);
    if (!rv || !q) {
        printf("Lib init failed %d %p\n", rv, q);
        return NULL;
    }

    root = calloc(1, sizeof(node_td));
    root->i = a[i];
    qpush(fd, root);
    i++;
    while (a[i] != INVALID) {
        insert_rtol(fd, a[i], a[i+1]);
        i += 2;
    }
    return root;
}

void
insert_val (node_td *node, int i, node_td *prev)
{
    node_td *nn;

    if (!node) {
        if (i > prev->i) {
            if (prev->right != NULL) {
                printf("Something wrong\n");
                return;
            }
            nn = calloc(1, sizeof(node_td));
            nn->i = i;
            prev->right = nn;
            return;
        } else {
            if (prev->left != NULL) {
                printf("Something wrong\n");
                return;
            }
            nn = calloc(1, sizeof(node_td));
            nn->i = i;
            prev->left = nn;
            return;
        }
    }

    prev = node;
    if (node->i < i) {
        insert_val(node->right, i, prev);
    } else {
        insert_val(node->left, i, prev);
    }
}

node_td *
cons_tree (int a[])
{
    int i = 0;
    node_td *root;
    
    root = calloc(1, sizeof(node_td));
    root->i = a[i];

    while (a[i] != INVALID) {
        insert_val(root, a[i], root);
        i++;
    }
    return root;
}
   
void
print_tr (node_td *node, char *str)
{
    printf("%s\n ", str);
    root = node;
    inorder(node);
    printf("\n");
}
