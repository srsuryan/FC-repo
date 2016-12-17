#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../ll/util.h"

/* given 2 arrays, find if these two arrays will form same bst or not */

int debug = 1;
void     
find_range (int i, int *minl, int *maxr, int match, int *a)
{
    *minl = *maxr = -1;

    while (i >= 0) {
        if (match < a[i]) {
            if (*maxr == -1) {
                *maxr = a[i];
            } else if (*maxr > a[i]) {
                *maxr = a[i];
            }
        } else {
            if (*minl == -1) {
                *minl = a[i];
            } else if (*minl < a[i]) {
                *minl = a[i];
            }
        }
        i--;
    }
}

int 
main (int argc, char *argv[])
{
    typedef struct range_ {
        int minl;
        int maxr;
    } range_td;
    range_td range[32] = {0};
    int i, j, si, sj, max, k;
    
    int a[] = {8, 3, 6, 1, 4, 7, 10, 14, 13, INVALID};
    int b[] = {8, 10, 14, 3, 6, 4, 1, 7, 13, INVALID};
#if 0
    int a[32] = {25, 30, 50, 60, 55, 52, 53, INVALID};
    int b[32] = {25, 30, 50, 60, 55, 53, 52, INVALID};
#endif
    i = j = 0;
    while ((a[i] != INVALID) && (b[j] != INVALID)) {
        i++;
        j++;
    }
    max = i-1;

    if (a[i] != b[j]) {
        printf("No of elements do not match\n");
        return 1;
    }
    if (debug) {
        printf("Both has %d elements\n", max);
    }
    if (si != sj) {
        printf("Does not have same no of elements\n");
        return 1;
    }
    i = 0;
    j = 0;

    while (a[i] == b[j]) {
        i++;
        j++;
    }

    if (i == j) {
        if (!j) {
            printf("Tree completely different\n");
            return 1;
        } else if (i == si) {
            printf("Tree completely same\n");
            return 1;
        }
    } else {
        printf("Tree nodes are not the same\n");
        return 1;
    }

    if (debug) {
        printf("Starting range check at %d from uncmon nodes %d %d\n", 
                i, a[i], b[i]);
    }
    k = 0;
    si = sj = i;
    while (si <= max) {
        if (a[si] == b[sj]) {
            si++;
            sj++;
            continue;
        }
        find_range(si-1, &range[k].minl, &range[k].maxr, a[si], a);
        find_range(sj-1, &range[k+1].minl, &range[k+1].maxr, b[sj], b);
        if (debug) {
            printf("a[%d]= %d min %d maxr %d\n", si, a[si], range[k].minl, range[k].maxr);
            printf("a[%d]= %d min %d maxr %d\n", sj, b[sj], range[k+1].minl, range[k+1].maxr);
            getchar();
        }
        si++;
        sj++;
        k +=2;
    }
}
