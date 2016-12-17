#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

/* http://www.geeksforgeeks.org/collect-maximum-points-in-a-grid-using-two-traversals/ */

#define ROW 5
#define COL 4

int debug = 1;

int mat[ROW][COL] = {
                     {3, 6, 8, 2},
                     {5, 2, 4, 3},
                     {1, 1, 20, 10},
                     {1, 1, 20, 10},
                     {1, 1, 20, 10}
                    };

int dp1[ROW][COL] = {0};
int dp2[ROW][COL] = {0};
int wk1[ROW][COL] = {0};
int wk2[ROW][COL] = {0};

enum {
    MAT = 0,
    DP1,
    DP2,
    WK1,
    WK2,
    MAX,
};

char whichmatstr[MAX][32] = {
    "MAT",
    "DP1",
    "DP2",
    "WK1",
    "WK2",
};

void mark_wk (int wk[][COL])
{
    int i, j;

    wk[0][0] = 1;
    for (i = 1; i < ROW/2+1; i++) {
        for (j = 0; (j < i+1); j++) {
             wk[i][j] = 1;
        }
    }
    j = 2;
    for (; i < ROW; i++) {
        memcpy(wk[i], wk[i-j], sizeof(int)*COL);
        j += 2;
    }
}

void prn (int mat[][COL], int wo)
{
    int i, j;

    printf("Printing mat %s %d\n", whichmatstr[wo], wo);
    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            printf("[%d][%d] = %d ", i, j, mat[i][j]);
        }
        printf("\n");
    }
}

int pick (int arr[][COL], int i)
{
   int j, idx = 0, max = arr[i][0];

   for (j = 1; j < COL; j++) {
        if (max <= arr[i][j]) {
            max = arr[i][j];
            idx = j;
        }
   }
   return idx;
}

int
main (int argc, char *argv[])
{
    int i, j, v;

    mark_wk(wk1);
    if (debug) {
        prn(wk1, WK1);
    }

    dp1[0][0] = mat[0][0];
    dp1[1][0] = mat[0][0]+mat[1][0];
    dp1[1][1] = mat[0][0]+mat[1][1];

    for (i = 1; i < ROW-1; i++) {
        dp1[i+1][0] = dp1[i][0]   + mat[i+1][0];
        dp1[i+1][1] = dp1[i][0]  + mat[i+1][1];
    }
    if (debug) {
        prn(dp1, DP1);
    }

    for (i = 1; i < ROW-1; i++) {
        for (j = 1; j < COL; j++) {
            if (wk1[i][j]) {
                if (wk1[i+1][j-1]) {
                    v = dp1[i][j] + mat[i+1][j-1];
                    if (v > dp1[i+1][j-1]) {
                        dp1[i+1][j-1] = v;
                    }
                }
                if (wk1[i+1][j]) {
                    v = dp1[i][j] + mat[i+1][j];
                    if (v > dp1[i+1][j]) {
                        dp1[i+1][j] = v;
                    }
                }
                if (wk1[i+1][j+1]) {
                    dp1[i+1][j+1] = dp1[i][j] + mat[i+1][j+1];
                }
            }
        }
    }

    if (debug) {
        prn(dp1, DP1);
    }
    for (i = ROW-2; i >= 0; i--) {
        dp1[i][pick(dp1, i)] = 0;
    }
    if (debug) {
        prn(dp1, DP1);
    }
}

