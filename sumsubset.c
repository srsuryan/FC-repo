#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "qlib.h"

/*
Given a set of non-negative integers, and a value sum, 
determine if there is a subset of the given set with sum equal to given sum.
Examples: set[] = {3, 34, 4, 12, 5, 2}, sum = 9
Output:  True  //There is a subset (4, 5) with sum 9.
*/

typedef struct subset_ {
    int arr[32];
    int mc;
    int incomp[32];
} subset;

subset ss[32] = {0};

int debug = 0;
int reachedsum = 0;

void
fillrecr (int sum, int *arr, int min, int max)
{
    int ndb, nde;

    if (max <= min) return;
    if (max <= 0) return;

    if (sum < 0) return;

    ndb = sum - arr[min];

    nde = sum - arr[max];

    if (!ndb || !nde) {
        reachedsum++;
        return;
    }

    printf("ndb %d sum %d arr[min=%d]=%d  a[max=%d]=%d\n",
            ndb, sum, min, arr[min], max, arr[max]);
    //getchar();
    fillrecr(ndb > 0 ? ndb : sum, arr, min+1, max);
    printf("nde %d sum %d arr[min=%d]=%d a[max=%d]=%d\n",
            nde, sum, min, arr[min], max, arr[max]);
    //getchar();
    fillrecr(nde > 0 ? nde : sum, arr, 0, max-1);
}


void
fill (int i, int *ref)
{
    int sum = i, cref[32] = {0}, set = 0;
    int j = i -1, mc, diff = 0;

    memcpy(cref, ref, sizeof(int)*32);
    if (debug) {
        printf("Find new path for i %d at j %d mc %d\n", i, j, ss[i].mc);
        getchar();
    }
   

    diff = sum;
    while ((j >= 0) && diff) {
        if (cref[j]) {
            mc = ss[i].mc;
            ss[i].arr[mc] = j;
            ss[i].mc++;
            ss[i].incomp[mc] = 1;
            diff = sum - j;
            sum = diff;
            cref[j]--;
            if (debug) {
                printf("Adding set %d at mc %d diff %d, cref %d %d\n",
                        j, mc, diff, cref[j], cref[j-1]);
                getchar();
            } 
            j = diff;
            set = 1;
        }
        if (!set) j--;
        set = 0;
    }
   
    /* If diff still exist, we need to traverse back and delete incomple denoms */ 
    if (diff) {
        mc = ss[i].mc;
        while (mc) {
            if (ss[i].incomp[mc]) {
                if (debug) {
                    printf(" undoing for i %d %d at mc %d \n", i, ss[i].arr[mc], mc);
                    getchar();
                }
                ss[i].arr[mc] = 0;
                ss[i].mc--;
                ss[i].incomp[mc] = 0;
            }
            mc--;
        }
    }
}


int 
main (int argc, char *argv[])
{
    int *a, ref[32] = {0}, sum, i;
    int b[32] = {2, 1, 4,  6, 5, 3};
    
    a = get_from_main(argc, argv);

    /* Assume first letter is the sum to be found */
    sum = a[0];
    if (sum >= 32) {
        return 0;
    }

    ref[0] = 0;
    for (i = 1; i < argc -1; i++) {
        if (a[i] <= sum) {
            ref[a[i]] = 1;
            if (debug) {
                printf("Ref for %d ref %d \n", a[i], ref[a[i]]);
            }
        }
    }

    fill(sum, ref);

    if (ss[sum].arr[0]) {
        i = 0;
        printf("\npath to %d are :: ", sum);
        while (i < ss[sum].mc) {
            printf("<< %d>>", ss[sum].arr[i]);
            i++;
        }
    }

    printf("\n");

    fillrecr(9, b, 0, 5);
    printf("Reglar met %d \n", reachedsum);

    return 1;
}


