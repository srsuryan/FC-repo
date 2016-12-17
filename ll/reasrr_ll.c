#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "util.h"
#include "ll.h"
#include "qlib.h":$


int debug = 1, fd;

sll *
rearrange (sll *n1)
{
    sll *n2, *start = NULL, *tempn;

    n2 = qpop();
    if (!n2) return NULL;

    n2->next = NULL;
    start = n1;
    while (n1 && n2 && (n1->next != n2)) {
        tempn = n1->next;
        n1->next = n2;
        n2->next = tempn;
        n1 = tempn;
        n2 = qpop();
        if (!n2) break; 
        n2->next = NULL;
    }

    return start;
}

int
main (int argc, char *argv[])
{
    int *a, i, rv, count = 0;
    sll *start, *node, *prev;
    stack_td *s;
        
    printf("argc %d\n", argc);
    rv = slib_init(STACK, &s, &fd);
    if (!rv || !s) {
        printf("Lib init failed %d %p\n", rv, s);
        return 1;
    }
    a = get_from_main(argc, argv);

    start = create_list(a);
    start = rearrange(start);
    node = start;
    while (node) {
        count++;
        node = node->next;
    }

    if (count%2) {
        printf("Invalid input\n");
        return 1;
    }
    i = 0;
    node = start;
    while (i <= count/2) {
        prev = node;
        node = node->next;
        i++;
    }
    
    printf("Prev %d i %d node %d, count %d\n", prev ? prev->i : -1, i, node->i, count);
    getchar();
    while (i < count) {
        qpush(node);
        node = node->next;
        i++;
    }
    start = rearrange(start);
    print_sl(start);
}
