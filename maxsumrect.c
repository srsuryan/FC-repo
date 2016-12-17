#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define ROW 4
#define COL 5

int debug = 0;

int mat[ROW][COL] = {
                       {1, 2, -1, -4, -20},
                       {-8, -3, 4, 2, 1},
                       {3, 8, 10, 1, 3},
                       {-4, -1, 1, 7, -6}
                    };
int sto[20][COL]; 

void
summation (int br, int ur, int sidx)
{
    int j;

    if (br == ur) {
        for (j = 0; j < COL; j++) {
            sto[sidx][j] = mat[br][j];
        }
        return;
    }

    for (j = 0; j < COL; j++) {
        sto[sidx][j] = sto[sidx - 1][j] + mat[ur][j];
        if (debug) {
            printf("sidx %d ur %d j %d %d %d", sidx, ur, j, sto[ur+1][j], mat[ur][j]);
            getchar();
        }
    }
}

int
get_lrgst_sa (int idx)
{
    int j, highest = -1, sum = 0;
    int dp[COL] = {0};

    dp[0] = sto[idx][0];

    for (j = 1; j < COL; j++) {
        sum = dp[j-1]+sto[idx][j];
        if ((sum >0) && (sum > sto[idx][j])) {
            dp[j] = sum;
            if (highest < sum) {
                highest = sum;
            }
        } else {
            dp[j] = sto[idx][j];
        }
    }

    return highest;
}

int 
main (int argc, char *argv[])
{
    int br, ur, sidx = 0, i, j, highest_rect, mrect = -1;

    for (br = ROW-1; br >= 0; br--) {
        for (ur = br; ur >= 0; ur--) { 
            summation(br, ur, sidx);
            sidx++;
        }
    }

    i = 0;
    while (i <= sidx) {
        highest_rect = get_lrgst_sa(i);
        if (debug) {
            printf("Idx %d highest is %d\n", i, highest_rect);
            getchar();
        }
        if (mrect < highest_rect) {
            mrect = highest_rect;
        }
        i++;
    }

    if (debug) {
        for (i = 0; i < sidx; i++) {
            for (j = 0; j  < COL; j++) { 
                printf("sto[%d][%d] = %d ",  i, j, sto[i][j]);
            }
            printf("\n");
        }
    }
    printf("Highest sum of sub matrix is %d\n", mrect);
}

