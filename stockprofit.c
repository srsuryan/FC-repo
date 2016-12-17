#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define ROW 32
#define COL ROW
int a[6] = {10, 22, 5, 75, 65, 80};
//int a[7] = {2, 30, 15, 10, 8, 25, 80};
//int a[7] = {100, 30, 15, 10, 8, 25, 80};
//int a[5] = {90, 80, 70, 60, 50};

int mat[ROW][COL] = {0};

typedef struct max_ {
    int val;
    int c;
    int nr;
} max_td;

max_td max[32] = {0};
int debug = 1;

void
const_mat (int c, int nr, int n)
{
    int pivot, j;

    pivot = mat[0][c];

    mat[nr][c] = 0;
    max[nr].c = c;
    max[nr].nr = nr;

    for (j = c+1; j < n; j++) {
        mat[nr][j] = mat[0][j] - pivot;
        if (max[nr].val < mat[nr][j]) {
            max[nr].val = mat[nr][j];
        }
    }
}

int get_prev_max (int r, int c)
{
    int lcm = -1, i, j;

    for (i = r; i >= 1; i--) {
        for (j = 0; j <= c; j++) {
           if (lcm < mat[i][j]) {
               lcm = mat[i][j];
            }
        }
    }

    if (debug) {
        printf("max for r %d, c %d is %d\n", r, c, lcm);
        getchar();
    }

    return lcm > 0 ? lcm : 0;
}

int 
main (int argc, char *argv[]) 
{
    int n, nr, i, j, lmax, sum, nmax;

    //if (argc <= 1) return 1;

    //n = strtol(argv[argc], 0, 0);

    n = sizeof(a)/sizeof(int);
    nr = 1;
    for (i = 0; i < n; i++) {
         mat[0][i] = a[i];
    }

    for (i = 0; i < n; i++) {
        const_mat(i, nr, n);
        nr++;
    }
    for (i = 1; i < n; i++) {
        if (debug) {
            printf("max %d col %d\n", max[i].val, max[i].c);
        }
        if (i == 1) {
            lmax = max[i].val;
            continue;
        }
        nmax = max[i].val;
        sum = nmax + get_prev_max(max[i].nr, max[i].c); 
        if (lmax < sum) {
            lmax = sum;
        }
    }
    printf("max sum %d\n", lmax);

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("mat[%d][%d] = %d ", i, j, mat[i][j]);
        }
        printf("\n");
    }

    return 0;
}

