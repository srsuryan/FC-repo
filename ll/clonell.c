#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "util.h"

typedef struct sll_ {
    int i;
    struct sll_ *next;
    struct sll_ *rptr;
} sll;

typedef struct sll_ext_ {
    struct sll_ *bptr;
    struct sll_ *sptr;
} sll_ext;
 
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
print_rlist (sll *n1)
{
    int max = -1, count = 0;
    sll *n2;

    printf("New rule ===================\n"); 
    while (n1) {
        if (max < n1->i) {
            max = n1->i;
        }
        count++;
        n2 = n1->rptr;
        printf(" %d %d %d max %d\n", n1->i, n2 ? n2->i : -1, count, max);
        n1 = n1->next;
    }
}

int
main (int argc, char *argv[])
{
    sll *start, *p1, *n2, *n1, *nn1;
    sll *startn, **lastn, *rn, *newn;
    int *a, count = 0, max = -1, i, ri;
    sll_ext b[32] = {0};

    a = get_from_main(argc, argv);

    start = create_list(a);

    n1 = start;
    while (n1 && n1->i != 3) {
        n1 = n1->next;
    }
    start->rptr = n1;

    n1 = start->next;
    n1->rptr = start;

    n1 = n1->next;
    p1 = n1;
    while (n1 && n1->i != 5) {
        n1 = n1->next;
    }
    n1->rptr = start->next;
    p1->rptr = n1;

    n1 = p1->next;
    n1->rptr = p1;

    n1 = start;
    while (n1) {
        if (max < n1->i) {
            max = n1->i;
        }
        count++;
        n2 = n1->rptr;
        printf(" %d %d %d max %d\n", n1->i, n2 ? n2->i : -1, count, max);
        n1 = n1->next;
    }

    free(a);
    //b = calloc(1, (count + 10)*sizeof(sll_ext *));
    n1 = start;
    while (n1) {
        i = n1->i;
        newn = calloc(1, sizeof(sll));
        if (!startn) {
            startn = newn;
            lastn = &startn->next;
        } else {
            *lastn = newn;
            lastn = &newn->next;
        }
        newn->i = i;
        b[i].sptr = newn;
        rn = n1->rptr;
        ri = rn->i;
        if (!b[ri].sptr) {
            b[ri].bptr = newn;//node 3 has pointer to 1, similarly node 5 has pointer to 3
        } else {
            nn1 = b[ri].sptr;
            newn->rptr = nn1;
        }
        if (b[i].bptr) {
            nn1 = b[i].bptr;
            nn1->rptr = newn;
        }
        n1 = n1->next;
        print_rlist(startn);
        getchar();
    }
}  
