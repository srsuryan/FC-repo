#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include "util.h"
//#include "ll.h"

int debug = 0;
#define INVALID 255
typedef struct tree_ {
    int i;
    struct tree_ *left;
    struct tree_ *right;
} tree;

typedef struct sll_ {
    int i;
    struct sll_ *next;
} sll;

sll *
create_list (int *a)
{
    sll *start, **last, *n;
    int i = 0;

    start = calloc(1, sizeof(sll));
    start->i = a[0];
    i = 1;
    last = &start->next;
    while (a[i] != INVALID) {
        n = calloc(1, sizeof(sll));
        n->i = a[i];
        *last = n;
        last = &n->next;
        i++;
    }

    return start;
}

void
print_sl (sll *n)
{
    while (n) {
        printf(" %d ", n->i);
        n = n->next;
    }
    printf("\n");
}
                          

sll*
get_midnode (sll *n, sll **a, sll **b)
{
    sll *s, *f, *p = NULL, *midp;

    if (!n || !n->next) {
        *a = *b = NULL;
        if (n) {
            return n;
        }
        return NULL;
    }

    s = f = n;
    while (n) {
        p = p ? p->next : s;
        f = n->next;
        f = f ? f->next : NULL;
        if (!f) break;
        n = f->next;
    }

    *a = s;
    midp = p->next; 
    *b = midp->next;
    p->next = NULL;
    midp->next = NULL;
    if (debug) {
        printf("A (%d %p) p (%d %p) M (%d %p) B (%d %p) \n", s->i, s->next, 
                p->i, p->next, midp->i, midp->next, (*b) ? (*b)->i : -1, (*b) ? (*b)->next : (*b));
        getchar();
    }
    return midp;
}

tree * 
treeform (sll *n)
{
    tree *node;
    sll *msll, *a, *b, *left = NULL, *right = NULL;

    msll = get_midnode(n, &a, &b);
    if (!msll) return NULL;
    node = calloc(1, sizeof(tree));
    node->i = msll->i;

    node->left = treeform(a);
    node->right = treeform(b);
#if 0
    left = treeform(a);
    if (left) {
        nodel = calloc(1, sizeof(sll));
        nodel->i = left->i;
    }
    node->left = nodel;
    right = treeform(b);
    if (right) {
        noder = calloc(1, sizeof(sll));
        noder->i = right->i;
    }
    node->right = noder;
#endif
    return node;
}

void
inorder (tree *node)
{
    if (!node) return;
    
    inorder(node->left);
    printf(" <<%d>> ", node->i);
    inorder(node->right);
}

int
main (int argc, char *argv[])
{
    int a[32] = {1, 2, 3, 4, 5, 6, 7, 8, INVALID}, flip = 1;
    tree *root;
    sll *start;

   // a = get_from_main(argc, argv);

    start = create_list(a);
    root = treeform(start);
    inorder(root);
    printf("\n");
}
