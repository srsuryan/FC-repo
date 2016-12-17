#include <stdio.h>
#include "ll.h"
#include "util.h"

int
main (int argc, char *argv[])
{
    int *a;
    sll *se, *so, **le = NULL, **lo = NULL, *node, *next;

    a = get_from_main(argc, argv);
    node = create_list(a);

    print_sl(node);
    getchar();
    while (node) {
        if (node->i%2 == 0) {
            if (!le) {
               // printf("Seg 3  \n" );
                //getchar();
                se = node;
                next = node->next;
                le = &se->next;
                node->next = NULL;
            } else {
                //printf("Seg  4\n" );
                //getchar();
                *le = node;
                le = &node->next;
                next = node->next;
                node->next = NULL;
            }
        } else {
            if (!lo) {
                //printf("Seg 1 \n" );
                //getchar();
                so = node;
                next = node->next;
                lo = &so->next;
                node->next = NULL;
            } else {
                //printf("Seg  2\n");
                //getchar();
                *lo = node;
                lo = &node->next;
                next = node->next;
                node->next = NULL;
            }
        }
        node = next;
    }
    print_sl(se);
    print_sl(so);
}
