#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define ROW 8
#define COL 8

int debug = 1;
#define REPLWITH 2
#define REPLBY 3

int mat[ROW][COL] = {{1, 1, 1, 1, 1, 1, 1, 1},
                      {1, 1, 1, 1, 1, 1, 0, 0},
                      {1, 0, 0, 1, 1, 0, 1, 1},
                      {1, 2, 2, 2, 2, 0, 1, 0},
                      {1, 1, 1, 2, 2, 0, 1, 0},
                      {1, 1, 1, 2, 2, 2, 2, 0},
                      {1, 1, 1, 1, 1, 2, 1, 1},
                      {1, 1, 1, 1, 1, 2, 2, 1},
                      };
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
msp (int i, int j)
{

   if (!check_boundary(i, j)) {
       return;
   }

   if (mat[i][j] != REPLWITH) {
       return;
   }

   mat[i][j] = REPLBY;

   msp(i+1, j);

   j++;
   while (j < COL) {
        msp(i, j);
        j++;
   }
}

int
main (int argc, char *argv[])
{
    int i, j;

    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            if (mat[i][j] == REPLWITH) {
                msp(i, j);
            }
        }
    }
    
    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
             printf(" %d ", mat[i][j]);
        }
        printf("\n");
    }
}

