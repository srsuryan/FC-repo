#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define ROW 2
#define COL 9

int debug = 0;

#if 0
int mat[ROW][COL] = {
                     {1, 2, 3, 4},
                     {5, 6, 7, 8},
                     {9, 10, 11, 12},
                     {13, 14, 15, 16},
                    };
#endif
int mat[ROW][COL] = {
                    { 1, 2, 3, 4, 5, 6, 7, 8, 9},
                    {11, 12, 13, 14, 15, 16, 17, 18, 19}
                    };

int nmat[COL][COL] = {0};

int 
map (int i, int j)
{
   if ((i >= ROW) || (j < 0)) return 0;
   if ((i == 0) && (j == COL-1)) {
       printf("i %d j %d NC %d\n", i, j, ROW-(i+1)); 
       getchar();
   } 
   return (ROW-(i+1)); 
}


int
main (int argc, char *argv[])
{
    int NR, NC, start, i, j;

    for (i = 0; i < ROW; i++) {
        start = 1;
        NR = 0;
        for (j = 0; j < COL;j++) {
            if (start) {
                NC = map(i, j);
                start = 0;
            }
            nmat[NR][NC] = mat[i][j];
            NR++;
        }
    }

    for (i = 0; i < COL; i++) {
        for (j = 0; j  < COL; j++) {
            if (nmat[i][j])
                printf("nmat[%d][%d] = %d ",  i, j, nmat[i][j]);
        }
        printf("\n");
    }

}
