#include <stdio.h>

int mat[32][32] = {0};

int
intrm_calc (int *wt, int *val, int r, int c, int dst)
{
    int max = -1, i, j, idx = dst - 1, sum;

    for (i = idx; i >= 1; i--) {
        if ((dst - i) < 0) break;
        sum = mat[i][c] + mat[dst - i][c];
        if (sum > max) {
            max = sum;
            mat[i][c] = mat[dst-i][c] = 0;
            mat[dst][c] = max;
        }
    }
    
    return max;
}

void
calc_knpsk (int *wt, int *val, int r, int c, int i, int n)
{
    int j;// c = wt[i];

    if (i < n) {
        mat[r][c] = val[i];
        j = r-1;//wt[i] -1;
    } else {
        mat[r][c] = 0;
        j = r - 1;
    }

    //printf("mat[%d][%d] = %d", c, c, val[i]);
    //getchar();
    
    for (; j > 0; j--) {
        mat[j][c] = val[j-1];
        printf("Lmat[%d][%d] = %d", j, c, val[j-1]);
        getchar();
    }    

    if (r > 2) {
       //intrm_calc(wt, val, r-1, c, r);
    }
}


int main()
{
    int val[] = {60, 100, 120};
    int wt[] = {1, 2, 3};
    //int val[] = {10, 4, 7, 18, 12, 31};
    //int wt[] = {  1, 3, 4,  5,  7, 10};
    int  W = 5, j;
    int n = sizeof(val)/sizeof(val[0]), i, w;

    mat[wt[0]][wt[0]] = val[0];

    for (i = 1; i < n; i++) {
         calc_knpsk(wt, val, wt[i], wt[i], i, n);
    }
    
    for (i = n; i <= W; i++) {
         calc_knpsk(wt, val, i, i, i, n);
    }

    for (i = 0; i <= W; i++) {
        for (j = 0; j <= W; j++) {
            printf("mat[%d][%d] = %4d ", i, j, mat[i][j]);
        }
        printf("\n");
    }
}
