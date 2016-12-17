#include <stdio.h>
#include "ll.h"
#include "util.h"

int
main (int argc, char *argv[])
{
    int *a;
    sll *pp, *p, *n, *start;

    a = get_from_main(argc, argv);
    start = create_list(a);

    pp = start;
    if (!pp) return 1;
    p = pp->next;
    
    while (p) {
        if (pp->i < p->i) {
            pp->next = NULL;
            start = p;
            pp = p;
            p = p->next;
        } else {
            break;
        }
    }

    n = p ? p->next : NULL;

    while (n) {
        if (p->i < n->i) {
            pp->next = n;
        } else {
            pp = p;
        }
        p = n;
        n = n->next;
    }
    print_sl(start);
}
