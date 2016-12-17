#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "util.h"
#include "ll.h"

int debug  = 1;
void
print_bb (int *a, int max)
{
    int i;

    for (i = 0; i < max; i++) {
        printf(" a %d ", a[i]);
    }
    printf("\n");
}

void
selsort_a (int *a, int max)
{
    int mval, temp, midx;
    int i, j;

    for (i = 0; i < max-1; i++) {
        midx = i;
        mval = a[i];
        for (j = i+1; j < max; j++) {
            if (mval > a[j]) {
                midx = j;
                mval = a[j];
            }
        }
        if (a[i] > mval) {
            temp = a[i];
            a[i] = mval;
            a[midx] = temp;
            printf("swap between idx i %d midx %d (%d %d)\n", i, midx, a[i], a[midx]);
            getchar();
        }
    }
}

void
selsort_ll (sll *start)
{
    sll *prev, *node, *midx, *nn;
    int mval, temp;
    int i, j;

    prev = NULL;
    node = start;
    while (node) {
        //if (prev) {
          //  lb1 = prev;
        //}
        prev = node;
        node = node->next;
    }
        
    for (node = start; node !=  prev; node = node->next) {
        midx = node; 
        mval = node->i; 
        for (nn = node->next; nn; nn = nn->next) {
            if (mval > nn->i) {
                midx = nn;
                mval = nn->i;
            }
        }   
        if (node->i > mval) {
            temp = node->i;
            node->i = mval;
            midx->i = temp;
            printf("swap between (%d %d)\n", node->i, midx->i);
            getchar();
        }
    }
}

sll *
selsort_ll2 (sll *start)
{
    sll *tempn = NULL, *prev, *pnode = NULL, *node;
    sll  *nn, *tpnn = NULL, *tnn = NULL, *pnn = NULL;
    int mval, temp;
    int dbgi;

    prev = NULL;
    node = start;
    while (node) {
        prev = node;
        node = node->next;
    }

    for (node = start; node; pnode = node, node = node->next) {
        mval = node->i;
        pnn = NULL;
        if (!node->next) break;
        for (nn = node->next; nn; pnn = nn, nn = nn->next) {
            if (mval > nn->i) {
                tpnn = pnn ;
                tnn = nn;
                mval = nn->i;
            }
        }

        if (node->i > mval) {
            dbgi = node->i;
            if (tpnn && !pnode) {
                tpnn->next = node;
                tempn = node->next;
                node->next = tnn->next;
                start = tnn;
                tnn->next = tempn;
                node = tnn;
                    if (debug) {
                        printf("1. Exchange btw %d node %d\n ", dbgi, mval);
                        print_sl(start);
                        getchar();
                    }
            } else if (pnode && tpnn) {
                tpnn->next = node;
                tempn = node->next;
                node->next = tnn->next;
                pnode->next = tnn;
                tnn->next = tempn;
                node = tnn;
                    if (debug) {
                        printf("2. Exchange btw %d  node %d\n ", dbgi, mval);
                        print_sl(start);
                        getchar();
                    }
            } else if (!pnode && !tpnn) {
                node->next = tnn->next;
                tnn->next = node;
                if (start == node) {
                    start = tnn;
                }
                node = tnn;
                    if (debug) {
                        printf("3. Exchange btw %d  node %d\n ", dbgi, mval);
                        print_sl(start);
                        getchar();
                    }
            } else if (!tpnn && pnode) {
                pnode->next = tnn;
                tempn = tnn->next;
                tnn->next = node;
                node->next = tempn; 
                node = tnn;
                    if (debug) {
                        printf("4. Exchange btw %d node %d\n ", dbgi, mval);
                        print_sl(start);
                        getchar();
                    }
            }
        } else {
        }
    }
    return start;
}


int
main (int argc, char *argv[])
{
    int *a;
    sll *start;

    printf("argc %d\n", argc);
    getchar();
    a = get_from_main(argc, argv);
    print_bb(a, argc-1);
    start = create_list(a);
    //print_sl(start);
    start = selsort_ll2(start);
    //print_bb(a, argc-1);
    print_sl(start);
}
