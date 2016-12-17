#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ROW 5
#define COL 5

int debug = 0;
#if 0
int
mat[ROW][COL] = {{0, 0, 0, 0},
                 {1, 1, 1, 1},
                 {1, 1, 0, 0},
                 {1, 1, 1, 0},
                };
int
mat[ROW][COL] = {{1, 1, 1, 1},
                 {1, 1, 0, 1},
                 {1, 1, 0, 0},
                 {1, 1, 0, 0},
                };
#endif

#if 0
int mat[ROW][COL] = {
                  {0, 1, 1, 0, 1},
                  {0, 0, 0, 0, 0},
                  {1, 1, 1, 0, 0},
                  {1, 1, 1, 1, 0},
                  {1, 1, 1, 1, 1}
                };
#endif

int mat[ROW][COL] = {
                      {0, 0, 1, 1, 0},
                      {0, 0, 0, 1, 0},
                      {1, 1, 1, 1, 0},
                      {0, 0, 0, 0, 0},
                      {1, 1, 1, 1, 1}
                    };

int
findrestmat (int rv, int cv, int i, int j)
{
    int newi, newj;

    newi = i+1;
    newj = j+1;
    while ((newi < ROW) && (newj < COL)) {
        if ((mat[newi][j] == rv) && 
                (mat[i][newj] == cv)) {
        } else {
            if (debug) {
                printf("rv %d cv %d i %d j %d\n", rv, cv, i, j);
                getchar();
            }
            return 0;
        }
        newi++; newj++;
    }

    newi = i-1;
    newj = j-1;
    while ((newi >= 0) && (newj >= 0)) {
        if ((mat[newi][j] == rv) && 
                (mat[i][newj] == cv)) {
        } else {
            return 0;
        }
        newi--; newj--;
    }

    return 1;
}

int
main (int argc, char *argv[])
{
    int i, j, rv;

    for (i = 0, j = 0; i < (ROW-1) && j < (COL -1); i++, j++) {
        if (i == 1) debug = 1;
        if (mat[i+1][j] ^ mat[i][j+1]) {
            rv = findrestmat(mat[i+1][j], mat[i][j+1], i, j);
            if (rv == 1) {
                printf("The sq matrix has row %d col %d"
                        " all %d and all %d\n", i, j, mat[i][j+1], mat[i+1][j]);
                return 0;
            }
        }
        if (debug) {
            printf("Failed for i %d j %d\n", i, j);
            getchar();
        }
    }

    printf(" does not meet criteria\n");
    return 0;
}
