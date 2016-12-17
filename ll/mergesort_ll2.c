#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "util.h"
#include "ll.h"

int debug  = 1;
sll *start, **lastg = NULL;

void
split (sll *n, sll **a, sll **b)
{
    sll *f, *p, *s = NULL, *orig = n;    

    if (!n) {
        *a = *b = NULL;
        return;
    } else if (n->next == NULL) {
        *a = *b = NULL;
        return;
    }
    
    while (n) {
        s =  (s == NULL) ? n : s->next;
        p = n;
        f = n->next;
        if (!f) break;
        p = f;
        f = f->next;
        n = f;
    }

    if (debug) {
        //printf("Slow pointer %d fast pointer %d \n", s->i, p->i);
        //getchar();
    }
    *a = orig;
    *b = s->next;
    s->next = NULL;
    p->next = NULL;
}

sll *
merge (sll *a, sll *b)
{
    sll *s = NULL, **last;

    if (!a || !b) return NULL;

    while (a && b) {
        if (a->i > b->i) {
            if (!s) {
                s = b;
                last = &s->next;
            } else {
                *last = b;
                last = &b->next;
            }
            b = b->next;
            (*last) = NULL;
        } else {
            if (!s) {
                s = a;
                last = &s->next;
            } else {
                *last = a;
                last = &a->next;
            }
            a = a->next;
            (*last) = NULL;
        }
    }
    *last = a ? a : b;
    return s;
}

sll *
mmergesort (sll *n)
{
    sll *a, *b;
    sll *s1, *s2, *s;
 
    if (!n) return NULL;
 
    split(n, &a, &b);

    s1 = mmergesort(a);
    s2 = mmergesort(b);

    s = merge(s1 ? s1 : a, s2 ? s2 : b);
    printf("Start from mmsort\n");
    print_sl(s);
    return s;
}

int
main (int argc, char *argv[])
{
    int *a;

    a = get_from_main(argc, argv);

    start = create_list(a);
    print_sl(start);
    start = mmergesort(start);
    printf("Start from Main\n");
    print_sl(start);
}
