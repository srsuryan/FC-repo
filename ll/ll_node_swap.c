#include <stdio.h>
#include "ll.h"
#include "util.h"

sll *
swap_ll (sll *p, sll *c, sll *n)
{
    sll *nn = NULL;

    if (c && n) {
        c->next = p; // <---p <--- c  n->nn
        nn = n->next;
        n->next = c; // p<---c <---- n (nn)---->
        if (debug) {
            print_sl(n);
            getchar();
        }
        return nn;
    }

    if (c) {
        c->next = p;
    }
        if (debug) {
            print_sl(c);
            getchar();
        }
    
    return NULL;
}

int
main (int argc, char *argv[])
{
    sll *p, *c, *n = NULL, *nn;
    int *a;

    a = get_from_main(argc, argv);
    p = create_list(a);
    
    if (debug) {
        sll *start = p;
        while (p) {
            printf(" %d ", p->i);
            p = p->next;
        } 
        p = start;
        printf("\n");
    }

    if (p) {
        c = p->next; // p -> c
        p->next = NULL;
        if (c) {
            n = c->next; // <--p c->n
        } else {
            return 0;
        }
    } else {
        return 0;
    }


    nn = swap_ll(p, c, n);
    while (nn) {
        c = nn->next; // 4nn -> 5c -> 6
        nn->next = n;// 3n <--- 4nn 5 ->6
        p = n; //3p <---4nn 
        n = c; 
        c = nn; // 3p <----4c --> 5c
        nn = swap_ll(p, c, n);//3p<----4c --->6n 
    }

    if (n) {
        print_sl(n);
    } else {
        print_sl(c);
    }
    return 0;
}
