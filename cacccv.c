#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* http://www.geeksforgeeks.org/how-to-print-maximum-number-of-a-using-given-four-keys/ */

int debug = 1;

typedef enum oper_ {
    CA = 0,
    CC,
    CV,
    CMAX,
} oper;

char str[CMAX][32] = {
    {"CA"},
    {"CC"},
    {"CV"}
};

typedef struct node_ {
     oper op;
     int  val;
     int  max;
     int base;
     struct node_ *next;
} node_td;

node_td a[32] = {0};

void
set_node (int idx)
{
    int max, pidx;
    node_td *pnode, *cnode, *prev, **last;

    a[idx].max = idx;
    a[idx].val = idx;
    max = a[idx].max;
    
    pidx = idx -1;
    pnode = a[pidx].next;
    last = &a[idx].next;
    prev = &a[idx];
    while (pnode) {
        cnode = calloc(1, sizeof(node_td));
        *last = cnode;
        if (pnode->op == CV) {
            cnode->op = CV;
        } else {
            cnode->op = (pnode->op+1);
            cnode->val = pnode->val;
            cnode->max = cnode->val;
        }
        //cnode->max = a[pidx].val+1;
        //max = cnode->max;
        if (cnode->op == CV) {
            cnode->val = pnode->base + pnode->val;
            cnode->base = pnode->base;
            if (cnode->val > max) {
                max = cnode->val;
            }
        } else if (cnode->op == CA) {
            cnode->val = a[pidx].max;
            cnode->base = cnode->val;
            if (cnode->val > max) {
                max = cnode->val;
            }
        } else if (cnode->op == CC) {
            cnode->val = pnode->val;
            cnode->base = pnode->base;
            if (cnode->val > max) {
                max = cnode->val;
            }
        }
        if (debug) {
            printf("P idx :: previous :: val %d max %d\n",
                    a[pidx].max, a[pidx].val);
            printf("C idx :: val %d max %d\n", a[idx].val, a[idx].max);
            printf("cnode :: val %d max %d, base %d op %s\n",
                    cnode->val, cnode->max, cnode->base, str[cnode->op]);
            printf("===============================\n");
            //getchar();
        }
        last = &cnode->next;
        pnode = pnode->next;
        prev = cnode;
    }
    cnode = calloc(1, sizeof(node_td));
    cnode->op = CA;
    cnode->val = a[pidx].max;
    cnode->base = a[pidx].max;
    prev->next = cnode;
    if (max > a[idx].max) {
        a[idx].max = max;
    }

}

int
main (int argc, char *argv[])
{
    int i;

    a[0].val = 0;
    a[1].val = 1;
    a[2].val = 2;
    a[3].val = 3;
    a[3].max = 3;

    for (i = 4; i <= 20; i++) {
        set_node(i);
    }

    printf("max for i %d max %d\n", i-1, a[i-1].max);
}

