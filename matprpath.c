#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define ROW 3
#define COL 3

int debug = 0;

#if 0
int mat[ROW][COL] = {
                        { 1,  2,  3,  4},
                        { 5,  6,  7,  8},
                        { 9, 10, 11, 12},
                        {13, 14, 15, 16},
                    };
#endif


int mat[ROW][COL] = { {1, 2, 3},
                      {4, 6, 5},
                      {3, 2, 1}
                    };

typedef struct mtn_ {
    int an;
    int tp;
    int ucn;
    int a[32][ROW+COL];
} mtn;

mtn dpt[ROW][COL] = {0};


int
main (int argc, char *argv[])
{
    int i, j, l_ucn, k, k2, tp = 0, ucn = 0;

    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            dpt[i][j].an = mat[i][j];
        }
    }
   
    /* Fill out initial paths */
    dpt[0][0].an = mat[0][0];
    dpt[0][0].tp = 1;
    dpt[0][0].ucn = 1;
    dpt[0][0].a[0][0] = mat[0][0];

    for (i = 1; i < ROW; i++) {
        dpt[i][0].an = mat[i][0];
        memcpy(dpt[i][0].a[0], dpt[i-1][0].a[0], sizeof(int)*dpt[i-1][0].ucn);
        dpt[i][0].ucn = dpt[i-1][0].ucn +1;
        l_ucn = dpt[i][0].ucn;
        dpt[i][0].a[0][l_ucn-1] = mat[i][0];
        dpt[i][0].tp = dpt[i-1][0].tp;
        if (debug) {
            printf("(%d 0) an %d tp %d ucn %d A \n", i,
                    dpt[i][0].an, dpt[i][0].tp, dpt[i][0].ucn);
            k = 0;
            while (k < dpt[i][0].ucn) {
                   printf("(..%d..) ",dpt[i][0].a[0][k]);
                   k++;
            }
        }
    }
    for (j = 1; j < COL; j++) {
        dpt[0][j].an = mat[0][j];
        memcpy(dpt[0][j].a[0], dpt[0][j-1].a[0], sizeof(int)*dpt[0][j-1].ucn);
        dpt[0][j].ucn = dpt[0][j-1].ucn +1;
        l_ucn = dpt[0][j].ucn;
        dpt[0][j].a[0][l_ucn-1] = mat[0][j];
        dpt[0][j].tp = dpt[0][j-1].tp;
        if (debug) {
            printf("(0 %d) an %d tp %d ucn %d A  \n", j,
                    dpt[0][j].an, dpt[0][j].tp, dpt[0][j].ucn);
            k = 0;
            while (k < dpt[0][j].ucn) {
                printf(" (..%d..) ", dpt[0][j].a[0][k]);
                k++;
            }
        }
    }

    for (i = 1; i < ROW; i++) {
        for (j = 1; j < COL; j++) {
            dpt[i][j].tp = dpt[i-1][j].tp + dpt[i][j-1].tp;
            dpt[i][j].ucn = dpt[i-1][j].ucn + 1;
            if (debug) {
                printf(" [%d %d] tp %d ucn %d <<%d %d>>\n", i, j, dpt[i][j].tp, dpt[i][j].ucn,
                    dpt[i-1][j].tp, dpt[i][j-1].tp);
            }
            k = 0;
            ucn = dpt[i][j].ucn;
            while (k < dpt[i-1][j].tp) {
                memcpy(dpt[i][j].a[k], dpt[i-1][j].a[k], sizeof(int)*dpt[i-1][j].ucn);
                dpt[i][j].a[k][ucn-1] = mat[i][j];
                k++;
            }
            k2 = k;
            k = 0;
            while (k < dpt[i][j-1].tp) {
                memcpy(dpt[i][j].a[k2], dpt[i][j-1].a[k], sizeof(int)*dpt[i][j-1].ucn);
                dpt[i][j].a[k2][ucn-1] = mat[i][j];
                k++;
                k2++;
            }
        }
    }
    tp = 0;
    i = ROW-1;
    j = COL-1;
    while (tp < dpt[i][j].tp) {
        ucn = 0;
        sum_coins = 0;
        while (ucn < dpt[i][j].ucn) {
            printf(" %d ", dpt[i][j].a[tp][ucn]);
            sum_coins += dpt[i][j].a[tp][ucn];
            ucn++;
        }
        printf("\n");
        tp++;
    }
}
