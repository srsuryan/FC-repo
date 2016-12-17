#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define ROW 3
#define COL 3

int mat[ROW][COL] = {
                        {-2, -3, 3},
                        {-5, -10, 1},
                        {10, 30, -5},
                    };
typedef struct dpm_ {
    int sum;
    int minpt;
} dpm;


dpm dp[ROW][COL] = {0};
/*
Minimum Initial Points to Reach Destination
*/

int 
main (int argc, char *argv[])
{
    int i, j;

    dp[0][0].sum = mat[0][0];
    if (dp[0][0].sum < 0) {
        dp[0][0].minpt = -1*dp[0][0].sum +1;
    }

    for (i = 1; i < ROW; i++) {
        dp[i][0].sum = dp[i-1][0].sum + mat[i][0];
        if (dp[i][0].sum < 0) {
            dp[i][0].minpt = -1*dp[i][0].sum +1;
        }
        if (dp[i][0].minpt < dp[i-1][0].minpt) {
            dp[i][0].minpt = dp[i-1][0].minpt;
        }
    }

    for (j = 1; j < COL; j++) {
        dp[0][j].sum = dp[0][j-1].sum + mat[0][j];
        if (dp[0][j].sum < 0) {
            dp[0][j].minpt = -1*dp[0][j].sum +1;
        }
        if (dp[0][j].minpt < dp[0][j-1].minpt) {
            dp[0][j].minpt = dp[0][j-1].minpt;
        }
    }
    
    for (i = 1; i < ROW; i++) {
        for (j = 1; j < COL; j++) {
            if (dp[i][j-1].minpt < dp[i-1][j].minpt) {
                dp[i][j].sum = dp[i][j-1].sum + mat[i][j];
                if (dp[i][j].sum < 0) {
                    dp[i][j].minpt = -1*dp[i][j].sum+1;
                }
                if (dp[i][j].minpt < dp[i][j-1].minpt) {
                    dp[i][j].minpt = dp[i][j-1].minpt;
                }
            } else {
                dp[i][j].sum = dp[i-1][j].sum + mat[i][j];
                if (dp[i][j].sum < 0) {
                    dp[i][j].minpt = -1*dp[i][j].sum+1;
                }
                if (dp[i][j].minpt < dp[i-1][j].minpt) {
                    dp[i][j].minpt = dp[i-1][j].minpt;
                }
            }
        }
    }

    printf("dP[2][2] = %d minpt %d\n", dp[2][2].sum, dp[2][2].minpt);
}

