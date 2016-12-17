#include <stdio.h>
#include "ll.h"
#include "util.h"

int debug = 1;
sll *start;

void
alt_swap (sll *p, sll *c,
          sll *n, sll *nn)
{
    c->next = nn; // 5->4->6->nn
    n->next = c; // 5->4
    if (p) {
        p->next = n;
    } else {
        start = n;
    }
}


int 
main (int argc, char *argv[])
{
    sll *node, *c, *n, *nn, *p;
    int *a;

    a = get_from_main(argc, argv);
    start = create_list(a);
    print_sl(start);

    node = start;
    p = NULL;
    while (node) {
        c = node;
        n = node->next;
        if (!n) break;
        nn = n->next;
        alt_swap(p, c, n, nn);
        if (debug) {
            print_sl(start);
            getchar();
        }
        p = node;
        node = node->next;
    }
    print_sl(start);
}
