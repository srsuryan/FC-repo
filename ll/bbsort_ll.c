#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "util.h"
#include "ll.h"

int debug = 1;
void
swap (int *a, int *b)
{
    int temp = *a;
    
    if (*a > *b) {
        *a = *b;
        *b = temp;
    }
}

void
swap_ll (sll *n1, sll *n2)
{

    int temp = n2->i;
    n2->i = n1->i;
    n1->i = temp;
}
   
void
swap_ll2 (sll *n1, sll *n2)
{
    n1->next = n2->next;
    n2->next = n1;
}
     
void
bbsort (int *a, int max)
{
    int count = 0, j;

    while (count < max-1) {
        for (j = 0; j < max-1; j++) {
            if (a[j] > a[j+1]) {
                swap(&a[j], &a[j+1]);
            }
        }
        count++;
    }
}

void
bbsort_ll (sll *start, sll *last)
{
    int count = 0, i;
    sll *node, *prev = NULL, *next;

    if (!start) return;

    if (!last) {
        last = start->next;
        while (last) {
            count++;
            prev = last;
            last = last->next;
        }
        last = prev;
    }

    if (!last) return;

    while (count) {
        for (node = start; node; node = node->next) {
            next = node->next;
            if (node->i > next->i) {
                swap_ll(node, next);
            }
            if (next == last) {
                break;
            }
        }
        count--;
    }
}

sll *
bbsort_ll2 (sll *start, sll *last)
{
    int count = 0, i, dbgi, lci;
    sll *node, *prev = NULL, *next, *pnext = NULL, *pnode = NULL, *tempn;

    if (!start) return NULL;

    if (!last) {
        last = start->next;
        while (last) {
            count++;
            prev = last;
            last = last->next;
        }
        last = prev;
    }

    if (!last) return NULL;

    while (count >= 1) {
        pnode = NULL;
        next = NULL;
        pnext = NULL;
        for (node = start; node; pnode = node, node = node->next) {
            if (next) {
                pnext = next;
            }
            pnext = NULL;
            next = node->next;
            if (!next) break;
            if (node->i > next->i) {
                dbgi = node->i;
                lci = next->i;
                if (pnode && pnext) {
                    pnode->next = next;
                    tempn = next->next;
                    next->next =  node->next;
                    pnext->next = node;
                    node->next = tempn;
                    node = next;
                    if (debug) {
                        printf("1. exchanging %d %d %p %p %d %d\n", dbgi, lci, pnode, pnext, pnode->i, pnext->i);
                        print_sl(start);
                        getchar();
                    }
                } else if (pnode && !pnext) {
                    pnode->next = next;
                    tempn = next->next;
                    next->next = node;
                    node->next = tempn;
                    node = next;
                    if (debug) {
                        printf("2. exchanging %d %d\n", dbgi, lci);
                        print_sl(start);
                        getchar();
                    }
                } else if (!pnode && pnext) {
                    pnext->next = node;
                    node->next = next->next;
                    next->next = pnode;
                    start = next;
                    node = next;
                    if (debug) {
                        printf("3. exchanging %d %d\n", dbgi, lci);
                        print_sl(start);
                        getchar();
                    }
                } else if (!pnode && !pnext) {
                    node->next = next->next;
                    next->next = node;
                    start = next;
                    if (debug) {
                        printf("4. exchanging %d %d\n", dbgi, lci);
                        print_sl(start);
                        getchar();
                    }
                    node = next;
                    //node remains same
                }
            }
        }
        count--;
    }
    return start;
}

void
print_bb (int *a, int max)
{
    int i;

    for (i = 0; i < max; i++) {
        printf(" a %d ", a[i]);
    }
    printf("\n");
}

int
main (int argc, char *argv[])
{
    int *a;
    sll *start;

    printf("argc %d\n", argc);
    a = get_from_main(argc, argv);
   
    start = create_list(a); 
    print_sl(start);
    start = bbsort_ll2(start, NULL);
    print_sl(start);
}
