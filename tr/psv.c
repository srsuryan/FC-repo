#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../qlib.h"
#include "../ll/util.h"

/*
 * Given two Binary Search Trees(BST), print the elements of both BSTs in sorted form. 
 * The expected time complexity is O(m+n) where m is the number of nodes in first tree 
 * and n is the number of nodes in second tree. Maximum allowed auxiliary space is O(height of the first tree + height of the second tree). 
 */

static int debug = 0;
static void
inorder (node_td *node)
{
    if (!node) return;

    inorder(node->left);
    printf(" In %d ", node->i);
    inorder(node->right);
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
    i = 1;
    while (a[i] != INVALID) {
        insert_val(root, a[i], root);
        i++;
    }
    return root;
}


node_td *
traverse (node_td *node, int fd)
{
    while (node) {
        spush(fd, node);
        node = node->left;
    }
    node = spop(fd);

    if (debug) {
        printf("poped Node %d\n", node->i);
    }

    return node;
}

void
psv (node_td *n1, node_td *n2, int fd1, int fd2)
{
    node_td *ln1, *ln2;

    ln1 = traverse(n1, fd1);
    ln2 = traverse(n2, fd2);
    
    while (ln1 && ln2) { 
        if (ln1 && ln2) {
            if (ln1->i < ln2->i) {
                printf(" %d ", ln1->i);
                ln1 = traverse(ln1->right, fd1);
            } else {
                printf(" %d ", ln2->i);
                ln2 = traverse(ln2->right, fd2);
            }
        } 
    }

    while (ln1) {
        ln1 = traverse(ln1, fd1);
        printf(" %d ", ln1->i);
        ln1 = ln1->right;
    }
    
    while (ln2) {
        ln2 = traverse(ln2, fd2);
        printf(" %d ", ln2->i);
        ln2 = ln2->right;
    }
}

int
main (int argc, char *argv[])
{
    node_td *r1, *r2;
    int a[32] = {60, 30, 10, 50, 70, 65, 80, INVALID};
    int b[32] = {55, 25, 15, 45, 65, 63, 75, INVALID};
    stack_td *s1, *s2;
    int rv, fd1, fd2;

    rv = slib_init(STACK, &s1, &fd1);
    if (!rv || !s1) {
        printf("Lib init failed %d %p\n", rv, s1);
        return 1;
    }

    rv = slib_init(STACK, &s2, &fd2);
    if (!rv || !s2) {
        printf("Lib init failed %d %p\n", rv, s1);
        return 1;
    }

    r1 = cons_tree(a);
    r2 = cons_tree(b);
    inorder(r1);
    printf("\n");
    inorder(r2);
    printf("\n");

    psv(r1, r2, fd1, fd2);
    printf("\n");
}
