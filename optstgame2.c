#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define u 0

/* http://www.geeksforgeeks.org/dynamic-programming-set-31-optimal-strategy-for-a-game/ */

int max = -1;
int debug = 1;

typedef struct node_td_ {
    int i;
    int beg;
    int end;
    int flag;
    struct node_td_ *left;
    struct node_td_ *right;
} node_td;

typedef struct llist_td_ {
    node_td *ptr;
    struct llist_td_ *next;
} llist_td;

node_td *root;
llist_td *start, **last;

void
inorder (node_td *node, int sum)
{
    if (!node) return;

    if (node->flag == u) {
        sum += node->i;
    }
    inorder(node->left, sum);

    if (debug) {
        printf(" %s %d %d %d f %d sum %d\n", (node == root) ? "ROOT" : "", 
                node->i, node->beg, node->end, node->flag, sum);
        //getchar();
    }

    if (sum > max) {
        max = sum;
    }

    inorder(node->right, sum);
}

void
cons_tree (int a[], int i, int n)
{
    node_td *node, *trl, *trr;
    llist_td *ll;
    
    root = calloc(1, sizeof(node_td));
    root->i = a[i];
    root->beg = (i == 0) ? 1 : 0;
    root->end = (i == 0) ? n-1 : n-2;
    root->flag = u;

    start = calloc(1, sizeof(llist_td));
    start->ptr = root;
    last = &start->next;

    while (start) {
        node = start->ptr;
        if (node->beg < node->end) {
            ll = calloc(1, sizeof(llist_td));
            trl = calloc(1, sizeof(node_td));
            trl->i = a[node->beg];
            trl->beg = node->beg+1;
            trl->end = node->end;
            ll->ptr = trl;
            *last = ll;
            last = &ll->next;
            node->left = trl;
            trl->flag =  (node->flag == 0) ? 1 : 0;

            ll = calloc(1, sizeof(llist_td));
            trr = calloc(1, sizeof(node_td));
            trr->i = a[node->end];
            trr->beg = node->beg;
            trr->end = node->end-1;
            ll->ptr = trr;
            *last = ll;
            last  = & ll->next;
            node->right = trr;
            trr->flag = (node->flag == 0) ? 1 : 0;
        }
        start = start->next;
    }
    inorder(root, 0);
}
    
int
main (int argc, char *argv[])
{
    //int a[] = {8, 15, 3, 7};
    int a[] = {5, 3, 7, 10};
    //int a[] = {2, 2, 2, 2};
    int n = sizeof(a)/sizeof(int);

    cons_tree(a, 0, n);
    cons_tree(a, n-1, n);
    printf(" max %d \n", max);
}
