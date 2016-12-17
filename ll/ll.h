#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "util.h"

int debug;
typedef struct sll_ {
    int i;
    struct sll_ *next;
} sll;

sll *
create_list (int *a)
{
    sll *start, **last, *n;
    int i = 0;

    start = calloc(1, sizeof(sll));
    start->i = a[0];
    i = 1;
    last = &start->next;
    while (a[i] != INVALID) {
        n = calloc(1, sizeof(sll));
        n->i = a[i];
        *last = n;
        last = &n->next;
        i++;
    }

    return start;
}

void
print_sl (sll *n)
{
    while (n) {
        printf(" %d ", n->i);
        n = n->next;
    }
    printf("\n");
}
