#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define ROW 6
#define COL 5

int mat[ROW][COL] =  {{0, 1, 1, 0, 1}, 
                   {1, 1, 0, 1, 0}, 
                   {0, 1, 1, 1, 0},
                   {1, 1, 1, 1, 0},
                   {1, 1, 1, 1, 1},
                   {0, 0, 0, 0, 0}};

int sto[ROW][COL] = {0};
int 
minof(int a, int b, int c)
{
  int m = a;
  if (m > b) 
    m = b;
  if (m > c) 
    m = c;
  return m;
}

int
check_boundary (int i, int j)
{

    if ((i >= ROW) && (i < 0)) {
        return 0;
    }

    if ((j >= COL) && (j < 0)) {
        return 0;
    }

    return 1;
}

void
calc_sq (int i, int j)
{
    sto[i][j] = minof(sto[i][j-1], sto[i-1][j-1], sto[i-1][j]) + 1;
}

int
main (int arc, char *argv[])
{
   int i, j;

   for (i = 0; i < ROW; i++) {
        sto[0][i] = mat[0][i];
   }

   for (j = 0; j < COL; j++) {
        sto[j][0] = mat[j][0];
   }

   for (i = 1; i < ROW; i++) {
      for (j = 1; j < COL; j++) {
         if (mat[i][j]) {
             calc_sq(i, j);
         }
      }
    }
   
    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
             printf("dp[%d][%d] = %d ", i, j, sto[i][j]);
        }
        printf("\n");
    }
}
