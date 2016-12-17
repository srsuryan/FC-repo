#include <stdio.h>
#include "ll.h"
#include "util.h"

sll *start2 = NULL, **last;

#define RPTC 2
int debug = 1;

sll *
rev_fn (sll *a[], int max)
{
    sll *node, *node2;
    int count = max-1;
    
    while (count >= 1) {
        a[count]->next = a[count-1];
        count--;
    }
    
    return a[max-1];
}

int
main (int argc, char *argv[])
{
    sll *a[32] = {0};
    sll *ll = NULL, *prev, *l, *node, *start = NULL, *f;
    int *b, count, mc = RPTC, skip = 0;

    b = get_from_main(argc, argv);
    node = create_list(b);

    if (!node) return 1;

    do {
        //skip = !skip;
        count = 0;
        memset(a, 0, sizeof(void *)*32);
        while ((count < RPTC) && (node)) {
            a[count] = node;
            count++;
            node = node->next;
        }
        printf("count %d %d\n", count, RPTC);
        getchar();
        f = rev_fn(a, count);
        
        if (!start) {
            start = f;
        } else {
            ll->next = f;
        }
        ll = a[0];
        ll->next = NULL;
   
        //skip = !skip;
        count = 0;
        while (!skip && node && count < RPTC) {
            if (!count)
                ll->next = node;
            prev = node;
            node = node->next;
            count++;
        }
        //if (!skip) {
            ll = prev;
       // }
    } while (node);

    print_sl(start);
}
