#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include "util.h"
//#include "ll.h"

int debug = 1;
#define INVALID 255
#if 0
typedef struct dll_ {
    int i;
    struct dll_ *left;
    struct dll_ *right;
} dll;
#endif

typedef struct dll_ {
    int i;
    struct dll_ *prev;
    struct dll_ *next;
} dll;

dll *
create_dlist (int *a)
{
    dll *start, *last, *n;
    int i = 0;

    start = calloc(1, sizeof(dll));
    start->i = a[0];
    i = 1;
    last = start;
    while (a[i] != INVALID) {
        n = calloc(1, sizeof(dll));
        n->i = a[i];
        last->next = n;
        n->prev = last;
        last = n;
        i++;
    }

    return start;
}

dll*
print_sl (dll *n)
{
    dll *prev;

    while (n) {
        printf(" %d ", n->i);
        prev = n;
        n = n->next;
    }
    printf("\n");
    return prev;
}

void
print_slr (dll *n)
{
    while (n) {
        printf(" %d ", n->i);
        n = n->prev;
    }
}
                          

dll*
get_midnode (dll *n, dll **a, dll **b)
{
    dll *s, *f, *p = NULL, *midp;


    if (!n || !n->next) {
        *a = *b = NULL;
        if (n) {
            n->prev = n->next = NULL;
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
    midp->prev = NULL;
    return midp;
}

dll * 
dllform (dll *n)
{
    dll *node;
    dll *mdll, *a, *b, *left = NULL, *right = NULL;

    node = get_midnode(n, &a, &b);

    if (a) 
        node->prev = dllform(a);
    if (b) 
        node->next = dllform(b);
    
    return node;
}

void
inorder (dll *node)
{
    if (!node) return;
    
    inorder(node->prev);
    printf(" <<%d>> ", node->i);
    inorder(node->next);
}

int
main (int argc, char *argv[])
{
    int a[32] = {1, 2, 3, 4, 5, 6, 7, 8, INVALID}, flip = 1;
    dll *root, *rev;
    dll *start;

   // a = get_from_main(argc, argv);

    start = create_dlist(a);
    rev = print_sl(start);
    print_slr(rev);
    getchar();
    root = dllform(start);
    inorder(root);
    printf("\n");
}
