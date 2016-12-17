#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node_td_ {
    int i;
    struct node_td_ *left;
    struct node_td_ *right;
} node_td;

#define INVALID 0xDEADBEEF

int debug = 0;
int n;
node_td *root = NULL;

void
inorder (node_td *node)
{

    if (!node) return;

    inorder(node->left);
    printf("Node %d ", node->i);
    inorder(node->right);
}

node_td *
mcons_tree (int *a, int min, int max)
{
    int mid;
    node_td *node;

    mid = (min+max)/2;

    if (a[mid] == INVALID) return NULL;
    
    if (min < 0) return NULL;

    if (max >= n) return NULL;

    node = calloc(1, sizeof(node_td));
    if (!root) {
        root = node;
    }

    node->i = a[mid];
    if (debug) {
        printf("mid %d node val %d\n", mid, node->i);
    }

    a[mid] = INVALID;
    node->left = mcons_tree(a, min, mid-1);
    node->right = mcons_tree(a, mid+1, max);
    return node;
}

int
main (int argc, char *argv[])
{
    node_td *node;
    int a[] = {10, 5, 4, 6, 30, 26, 37, 28};

    n = sizeof(a)/sizeof(int);
    printf("size is %d\n", n);
    getchar();
    mcons_tree(a, 0, n-1);
    inorder(root);
    printf("\n");
}

