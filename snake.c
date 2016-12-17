#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Given a n*n matrix where numbers all numbers are distinct and are distributed from range 1 to n2, find the maximum length path (starting from any cell) such that all cells along the path are increasing order with a difference of 1.

We can move in 4 directions from a given cell (i, j), i.e., we can move to (i+1, j) or (i, j+1) or (i-1, j) or (i, j-1) with the condition that the adjacen

Example:

Output: 4
The longest path is 6-7-8-9. 
*/

#define ROW 4
#define COL 4

#if 0
int  mat[ROW][COL] = {
                  {1, 2, 9},
                  {4, 0, 8},
                  {5, 6, 7}
                    };
#endif

int mat[ROW][COL] = {
                {9, 6, 5, 2},
                {8, 7, 6, 5},
                {7, 3, 1, 6},
                {1, 1, 1, 7}
                }; 
int dp[ROW][COL] = {0};

int 
lpath (int i, int j, int cost)
{
    int none = 0;

    if (i< 0 || i >= ROW) return 0;
    if (j<0 || j >= COL) return 0;

    if (dp[i][j]) return dp[i][j];

    if ((i+1 < ROW) && abs(mat[i+1][j] - mat[i][j]) == 1) {
        dp[i][j] = cost;
        lpath(i+1, j, cost+1);
        none = 1;
    }
#if 0
    if ((i-1 >= 0) && abs(mat[i-1][j] - mat[i][j]) == 1) {
        dp[i][j] = cost;
        lpath(i-1, j, cost+1);
    }
    if ((j-1 >= 0 ) && abs(mat[i][j-1] - mat[i][j]) == 1) {
        dp[i][j] = cost;
        lpath(i, j-1, cost+1);
    }
#endif
    if ((j+1 < COL) && abs(mat[i][j+1] - mat[i][j]) == 1) {
        dp[i][j] = cost;
        lpath(i, j+1, cost+1);
        none = 1;
    }

    if (!none) 
        dp[i][j] = cost;

    return dp[i][j];
}

int
main (int argc, char *argv[])
{
  int i, j, rv, high = -1;

  for (i = 0; i < ROW; i++) {
      for (j = 0; j < COL; j++) {
        rv = lpath(i, j, 1);
        if (high < rv) {
            high = rv;
        }
      }
    }
  for (i = 0; i < ROW; i++) {
      for (j = 0; j < COL; j++) {
            printf("dp[%d][%d] = %d ", i, j, dp[i][j]);
      }
      printf("\n");
  }  
  printf("Higest %d\n", high);
}
