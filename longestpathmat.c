#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ROW 3
#define COL 3
int mat[ROW][COL] = {
                      {1, 2, 9},
                      {5, 3, 8},
                      {4, 6, 7},
                    };
int dp[ROW][COL];

    int 
get_longest_path (int i, int j)
{

    if (dp[i][j] != -1) return dp[i][j];

    if ((j+1 < COL) && (mat[i][j]+1 ==
            mat[i][j+1])) {
        dp[i][j] = get_longest_path(i,j+1) +1;
    }
    if ((i+1 < ROW) && (mat[i][j]+1 ==
            mat[i+1][j])) {
        dp[i][j] = get_longest_path(i+1,j) +1;
    }
    if ((j-1 >= 0) && (mat[i][j]+1 ==
            mat[i][j-1])) {
        dp[i][j] = get_longest_path(i,j-1) +1;
    }
    if ((i-1 >= 0) && (mat[i][j]+1 ==
            mat[i-1][j])) {
        dp[i][j] = get_longest_path(i-1,j) +1;
    }

    if (dp[i][j] == -1) dp[i][j] = 1;
    return dp[i][j];
}

int
main (int argc, char *argv[])
{
    int i, j;

    memset(dp, -1, sizeof(int)*ROW*COL);

    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            get_longest_path(i, j);
        }
    }
    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            printf("dp[%d][%d] = %d ", i, j, dp[i][j]);
        }
        printf("\n");
    }
}
