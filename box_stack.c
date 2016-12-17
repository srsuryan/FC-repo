#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int debug = 0;
typedef struct box_
{
    int w, d, h; 
} Box;

typedef struct dps_ {
    int dp;
    int bidx;
    Box bxs; 
} dps_td;

dps_td dps[32] = {0};

int 
compare (const void *a, const void * b)
{
    int w1, w2, d1, d2;

    d1 = (*(Box *)b).d ;
    d2 = (*(Box *)a).d ;
    w1 = (*(Box *)b).w ;
    w2 = (*(Box *)a).w ;
    
    return d1*w1 - d2*w2;
}

int
lis (Box bst[], int max)
{
    int i, j, maxc = -1;

    for (i = 1; i < max; i++) {
        dps[i].bxs.w = bst[i].w;
        dps[i].bxs.d = bst[i].d;
        dps[i].bxs.h = bst[i].h;
        for (j = i-1; j >= 0; j--) {
            if ((bst[j].w > bst[i].w) && 
                    (bst[j].d > bst[i].d)) {
                if (dps[i].dp < dps[j].dp +1) {
                    dps[i].dp = dps[j].dp +1;
                    dps[i].bidx = j;
                }
                if (maxc < dps[i].dp) {
                    maxc = dps[i].dp;
                    break;
                }
            }
        }
    }
    return maxc;
}

/* Driver program to test above function */
int main()
{
    int i, maxc;
    Box arr[] = { {4, 6, 7}, {1, 2, 3}, {4, 5, 6}, {10, 12, 32} };
    int n = sizeof(arr)/sizeof(arr[0]);
    Box bst[n*6], *bsp;
    dps_td *dpsw;

    printf("The maximum possible height of stack is\n");


    for (i = 0; i < 32; i++) dps[i].dp = 1;

    for (i = 0; i < n; i++) {
        bst[6*i].w = arr[i].w;
        bst[6*i].d = arr[i].d;
        bst[6*i].h = arr[i].h;

        bst[6*i+1].w = arr[i].w;
        bst[6*i+1].d = arr[i].h;
        bst[6*i+1].h = arr[i].d;

        bst[6*i+2].w = arr[i].d;
        bst[6*i+2].d = arr[i].w;
        bst[6*i+2].h = arr[i].h;

        bst[6*i+3].w = arr[i].d;
        bst[6*i+3].d = arr[i].h;
        bst[6*i+3].h = arr[i].w;

        bst[6*i+4].w = arr[i].h;
        bst[6*i+4].d = arr[i].d;
        bst[6*i+4].h = arr[i].w;

        bst[6*i+5].w = arr[i].h;
        bst[6*i+5].d = arr[i].w;
        bst[6*i+5].h = arr[i].d;
    }

    qsort(bst, n*6, sizeof(bst[0]), compare);

    memcpy(&dps[0].bxs, &bst[0], sizeof(bst[0]));
    maxc = lis(bst, n*6);
    if (debug) {
        for (i = 0; i < n*6; i++) {
            printf("DP %d Box (%d %d %d) %d BIDX %d\n", 
                    dps[i].dp, bst[i].w, bst[i].d, bst[i].h, dps[i].dp, dps[i].bidx);
        }
    }

    int lbidx = n*6 - 1, bidx, ht = 0;
    printf(" Maxc %d \n", maxc);
    while (lbidx >= 0) {
        ht = 0;
        if (dps[lbidx].dp != maxc) {
            lbidx--;
            continue;
        } 
        bidx = lbidx;
        while (bidx > 0) {
            ht += dps[bidx].bxs.h;
            printf("Box (%d %d %d) %d-> ", dps[bidx].bxs.w, dps[bidx].bxs.d, dps[bidx].bxs.h, 
                    dps[bidx].bidx);
            bidx = dps[bidx].bidx;
        }
        lbidx--;
        printf("Ht %d\n", ht);
    }
    return 0;
}
