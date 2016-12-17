#include <stdio.h>
#include "ll.h"
#include "util.h"

sll *start2 = NULL, **last;

sll *
split_ll (sll *p, sll *n)
{

   p->next = n->next;
   n->next = NULL;
   *last = n;
   last = &n->next;
   return p;
}

int
main (int argc, char *argv[])
{
    sll *start, *start2 = NULL, *p, *node;
    int *a;

    a = get_from_main(argc, argv);
    start = create_list(a);

    node = start;
    p = NULL;
    do {
        while (node && (node->i == 0)) {
            p = node;
            node = node->next;
        }
        if (node && !start2) {
            start2 = node;
            p->next = node->next;
            last = &start2->next;
            node = p->next;
        } else if (node) {
            node = split_ll(p, node);
        }
    } while (node);

    print_sl(start);
    print_sl(start2);
}
