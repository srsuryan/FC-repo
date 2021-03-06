#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int debug = 0;
typedef struct adjacent_ {
    int an;
    int maxadj;
    int adj[8];
} adjacent;

adjacent hash[10] = {0};

typedef struct dpst_ {
    int an[10];
    int count;
    struct dpst_ *next;
} dpst;

dpst dparr[10] = {0};

void 
hash_add (int val, int *a, int count)
{
    hash[val].an = val;      
    memcpy(hash[val].adj, a, sizeof(int)*count);
    hash[val].maxadj = count;
}

void
construct_dps (int idx, dpst *dpn)
{
    static dpst **last = NULL;
    dpst *dp_node;
    int i = 0;

    if (!dparr[idx].next) {
        last = &dparr[idx].next;
    }

    dp_node = calloc(1, sizeof(dpst));
    memcpy(dp_node->an,  dpn->an, sizeof(int)*dpn->count);
    dp_node->an[dp_node->count] = dpn->an[0];
    dp_node->count++;    
    *last = dp_node;
    last = &dp_node->next;
    dparr[idx].count++;

    dparr[idx].an[0] = idx;
    while (i < hash[dpn->an[0]].maxadj) {
        dp_node = calloc(1, sizeof(dpst));
        memcpy(dp_node->an,  dpn->an, sizeof(int)*dpn->count);
        dp_node->count = dpn->count+1;
        dp_node->an[dp_node->count-1] = hash[dpn->an[0]].adj[i];
        if (debug) {
            printf(" hash val of %d adj is %d", dpn->an[0], hash[dpn->an[0]].adj[i]);
            getchar();
        }
        i++;
        *last = dp_node;
        last = &(dp_node->next);
        dparr[idx].count++;
    }
}

int 
main (int argc, char *argv[])
{
   int i = 0, j = 0, a[10];
   dpst *dpn, *dpn_p;
    
    a[0] = 8;
    hash_add(0, a, 1);
    a[0] = 2;
    a[1] = 4;
    hash_add(1, a, 2);
    a[0] = 1;
    a[1] = 5;
    a[2] = 3;
    hash_add(2, a, 3);
    a[0] = 2;
    a[1] = 6;
    hash_add(3, a, 2);
     
    a[0] = 1;
    a[1] = 5;
    a[2] = 7;
    hash_add(4, a, 3);
    a[0] = 2;
    a[1] = 4;
    a[2] = 8;
    a[3] = 6;
    hash_add(5, a, 4);
    a[0] = 3;
    a[1] = 5;
    a[2] = 9;
    hash_add(6, a, 3);
    a[0] = 4;
    a[1] = 8;
    hash_add(7, a, 2);
    a[0] = 7;
    a[1] = 5;
    a[2] = 9;
    a[3] = 0;
    hash_add(8, a, 4);
    a[0] = 6;
    a[1] = 8;
    hash_add(9, a, 2);

    if (debug) {
        while (i < 10) {
            j = 0;
            while (j < hash[i].maxadj) {
                printf("Hash val %d adj %d\n", hash[i].an, hash[i].adj[j]);
                j++;
            }
            i++;
        }
    }
    /* Populate it initially */
    i = 0;
    while (i < 10) {
        dpn = calloc(1, sizeof(dpst));
        dpn->an[0] = i;
        dpn->count = 1;
        dpn_p = dparr[1].next;
        dparr[1].next = dpn;
        dpn->next = dpn_p;
        i++;
    }

    i = 2; 
    while (i < 4) {
        dpn = dparr[i-1].next;
        while (dpn) {
            if (debug) {
                printf("Dpn %d \n", dpn->an[0]);
            }
            construct_dps(i, dpn);
            dpn = dpn->next;
            //break;
        }
        i++;
    }

    dpn = dparr[3].next;
    while (dpn) {
        if (debug) {
            printf("Dpn <%d %d %d %d> count %d OVC %d\n", 
                    dpn->an[0], dpn->an[1], dpn->an[2], dpn->an[3], 
                    dpn->count, dparr[2].count);
        }
        dpn = dpn->next;
    }
    printf("Dpn Tot %d %d %d %d\n",dparr[1].count, dparr[2].count, dparr[3].count, dparr[4].count);
}
