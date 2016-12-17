#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "util.h"
#include "ll.h"

int debug = 1;
static sll *l = NULL, *start;

sll *
rearr_zz (sll *b, int flip)
{
    sll *a, *temp, *s = NULL;
    static sll *ll;

    a = l;
    if (!a) return NULL;
    
    if (flip) {
        if (a->i < b->i) {
            temp = b->next;
            a->next = b;
            b->next = NULL;
            ll = a;
            l = b;
            if (debug) {
                printf("POS1 \n");
                print_sl(start);
                getchar();
            }
        } else if (a->i > b->i) { //2 1 3 4
            printf("POS2 a %d b %d\n", a->i, b->i);//11->20->15 (a) 5(b)
            temp = b->next;
            ll->next = b;
            b->next = a;
            a->next = NULL; //s (1->2->*)
            if (a == start) {
                start = b;
            }
            ll = b; // 11->20->5(b)->15(a) 
            l = a;
            if (debug) {
                printf("POS2.\n");
                print_sl(start);
                getchar();
            }
        }    
    } else {
        if (a->i > b->i) {
            temp = b->next;
            a->next = b;
            b->next = NULL;
            ll = a;
            l = b;
            if (debug) {
                printf("POS3.\n");
                print_sl(start);
                getchar();
            }
        } else if (a->i < b->i) {
            //1->2 ;  3->4
            printf(" %d -> %d (%d)\n", ll->i, l->i, b->i);
            ll->next = b;
            temp = b->next;
            b->next = a;//1 -> 3 -> 2->*
            ll = b;
            l = a;
            if (debug) {
                printf("POS4.\n");
                print_sl(start);
                getchar();
            }
        }
    }
    return temp;
}

int
main (int argc, char *argv[])
{
    int *k, flip = 1;
    sll *a, *b;
        
    printf("argc %d\n", argc);
    k = get_from_main(argc, argv);

    start = create_list(k);
    a = start;
    l = a;
    if (!a) return 0;
    b = a->next;
    do {
        if (!b) break;;
        b = rearr_zz(b, flip);
        printf("3.after reaarange \n");
        print_sl(start);
        flip = !flip;
    } while (1);

    print_sl(start);
    return 1;
}
