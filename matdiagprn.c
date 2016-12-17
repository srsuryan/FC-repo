#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define ROW 4
#define COL 4

int mat[4][4]  = {
                 {1, 2, 3, 4},
                 {5, 6, 7, 8},
                 {9, 10, 11, 12},
                 {13, 14, 15, 16}
                 };
int sto[8][8] = {0};

int
main (int argc, char *argv[])
{
    int rw[ROW] = {0};
    int alter = 0, j, i, comp_row = 0, cr;

    for (i = 0; i < ROW; i++) {
        alter = 0;
        for (j = 1, cr = i; j < COL; j++) {
            if (comp_row == 0) {
                cr++;
                sto[cr][j] = mat[i][j];
                printf(" cr %d j %d mat %d", cr, j, mat[i][j]);
                getchar();
                if (j == COL-1) {
                    comp_row++;
                }
            } else if (comp_row == 1) {
                cr++;
                sto[cr][j] = mat[i][j];
                printf(" cr2 %d j %d mat %d", cr, j, mat[i][j]);
                getchar();
                if (j == COL-1) {
                    comp_row++;
                    cr--;
                }
            } else {
                cr++;
                printf(" cr4 %d j %d mat %d sto %d alter %d", cr, j, mat[i][j], sto[cr][j], alter);
                getchar();
                if (!sto[cr][j] && !alter) {
                    sto[cr][j] = mat[i][j];
                    alter = 1;
                } else {
                    alter = 1;
                    if (j == COL-1) {
                        sto[cr][j-1] = mat[i][j];
                    } else if (!sto[cr][j]) {
                        sto[cr][j] = mat[i][j];
                    } else {
                        sto[cr][j-1] = mat[i][j];
                    }
                }
            }
        }
    }

    for (i = 0; i < 2*(ROW); i++) {
       for (j = 0; j < COL; j++) {
           //if (sto[i][j]) {
               printf(" %d ", sto[i][j]);
           //}
       }
       printf("\n");
    }
}

