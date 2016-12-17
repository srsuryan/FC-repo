#include <stdio.h>
#include "ll.h"
#include "util.h"

int debug = 1;

sll *
merge_ll3 (sll *n1, sll *n2) 
{
    sll *pn1, *pn2, *s1, *s2;
    int skip;

    s1 = n1;
    s2 = n2;
    pn1 = pn2 = NULL;
    while (n1 && n2) {
        skip = 0;
        while (n1 && n2 && (n2->i <= n1->i)) {
            pn2 = n2;
            n2 = n2->next;
            skip = 1;
        }


        while (!skip && (n1 && n2) && n1->i < n2->i) {
            pn1 = n1;
            n1 = n1->next;
        }

        if (!n1 || !n2) break;

        if (pn1 && !pn2) {
            if (debug) {
                printf("1. Choosing %d %d for swap [pn1 %d, pn2 NULL] [s2 %d]\n", n1->i, n2->i, pn1->i, s2 ? s2->i : -1);
                getchar();
            }
            pn1->next = n2;
            s2 = n2->next;
            printf("s2 %d \n", s2 ? s2->i : -1);
            n2->next = n1;
            pn1 = n2;
            n2 = s2;
        } else if (pn2 && !pn1) {
            if (debug) {
                printf("2. Choosing %d %d for swap [pn1 NULL, pn2 %d]\n", n1->i, n2->i, pn2->i);
                getchar();
            }
            s1 = s2;
            pn2->next = n1;
            pn1 = n1;
            n1 = n1->next;
            pn2 = NULL;
        } else if (pn1 && pn2) {
            if (debug) {
                printf("1. Choosing %d %d for swap [pn1 %d, pn2 %d]\n", n1->i, n2->i, pn1->i, pn2->i);
                getchar();
            }
            pn1->next = s2;
            pn2->next = n1;
            s2 = n2;
            pn1 = pn2;
            pn2 = NULL;
        } else { /* !pn1 && !pn2 */
            printf(" Should not happen \n");
        }
    }

    printf(" n1 %d n2 %d pn2 %d pn1 %d\n", n1 ? n1->i : -1, n2 ? n2->i : -1, pn2 ? pn2->i : -1, pn1 ? pn1->i : -1);
    if (n1 && !n2) {
        printf("4. Final Merge pn1 %d\n", pn1->i);
        getchar();
        pn1->next = pn2;
        pn2->next = n1;
    } else if (!n1 && n2) {
        pn1->next = n2;
    }

    return s1;
}



sll *
merge_ll2 (sll *n1, sll *n2)
{
    sll *s = NULL, **last;

    if (!n1 || !n2) return NULL;

    while (n1 && n2) {
        if (n1->i < n2->i) {
            if (!s) {
                s = n1;
                last = &s->next;
            } else {
                *last = n1;
                last = &n1->next;
            }
            n1 = n1->next;
        } else {
            if (!s) {
                s = n2;
                last = &s->next;
            } else {
                *last = n2;
                last = &n2->next;
            }
            n2 = n2->next;
        }
    }

    if (n1 && !n2) {
        *last = n1;
    } else if (!n1 && n2) {
        *last = n2;
    }

    return s;
}

sll *
merge_ll (sll *n1, sll *n2)
{
    sll *prev, *s1, *s2, *p1, *t2, *nn1 = NULL;
    int nsd;

    if (!n1 || !n2) return NULL;

    s1 = n1;
    s2 = n2;
    while (n2) {
        while (n1 && n2) {
            if (n2->i >  n1->i) {
                nsd = n1->i;
                p1 = n1;
                n1 = n1->next;
                p1->next = n2;
                t2 = n2->next;
                nn1 = n1->next;
                n2->next = n1;
                n1 = n2;
                nsd = n2->i;
                n2 = t2;
                s2 = t2;
                prev = nn1;
                while (n1 && (n1->i == nsd)) {
                        prev = n1;
                        n1 = n1->next;
                }
                if (prev) n1 = prev;
                prev = NULL;
                printf("n1 %d n2 %d\n", n1->i, n2->i);
                print_sl(s1);
                print_sl(s2);
                getchar();
            } else {
                printf("n1 %d n2 %d\n", n1->i, n2->i);
                getchar();
                if (!p1) {
                    s1 = n2;
                    s2 = n2->next;
                    n2->next = n1;
                    n2 = s2;
                } else {
                    p1->next = n2;
                    t2 = n2->next;
                    n2->next = n1;
                    n1 = n2;
                    n2 = t2;
                }
            }
        }

        if (!n1) {
            p1->next = n2;
            return s1;
        }
    }

    return s1;
}

int
main (int argc, char *argv[])
{
    sll *start, *s2 = NULL, *node;
    int *a;

    a = get_from_main(argc, argv);
    start = create_list(a);
    
    node = start;
    while (node && node->i != 255) {
        node = node->next;
    }
  
    if (!node) return 1; 
    s2 = node->next;
    node->next = NULL;
    node = merge_ll3(start, s2);
    print_sl(node); 

    return 0;
}
