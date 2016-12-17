#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ROW 4
#define COL ROW

typedef struct jobsched_ {
    int st;
    int ft;
    int profit;
} jobsched;

jobsched jsched[ROW] = {
                         {1, 2, 50},
                         {3, 5, 20},
                         {6, 19, 100},
                         {2, 100, 200},
                       };

int job[32] = {0};
int debug = 0;

int mat[ROW][COL] = {0};

void
form_mat ()
{
    int i, j, ft;

    for (i = 0; i < ROW; i++) {
        //mat[i][i] = 1;
        for (j = i+1; j < ROW; j++) {
            if (jsched[j].st >= jsched[i].ft) {
                mat[i][j] = 1;
            }
        }
    }
    if (debug) {
        for ( i = 0; i < ROW; i++) {
            for (j = 0; j < COL; j++) {
                printf(" %d ", mat[i][j]);
            }
            printf("\n");
        }
    }
    getchar();
}

int
calc_profit (int r, int sum)
{
    int i, j, mp[ROW] = {0}, maxv = 0, set = 0;

    for (i = r; i < ROW; i++) {
        for (j = r+1; j < COL; j++) {
            if (mat[i][j]) {
                mp[j] = calc_profit(j, sum + job[r]);
                set = 1;
                if (debug) {
                    printf("i %d mp[j=%d] = %d\n", i, j, mp[j]);
                    getchar();
                }
            }
        }
    }

    if (set) {
        maxv = mp[r+1];
        for (j = r+2; j < COL; j++) {
            if (maxv < mp[j]) {
                maxv = mp[j];
            }
        }
    } else return job[r] + sum;

    return maxv + sum;
}

int
main (void)
{
    int i, j, max_profit = -1, sum = 0;

    for (i = 0; i < ROW; i++) {
        job[i] = jsched[i].profit;
    }

    form_mat();

    for (i = 0; i < ROW; i++) {
        for (j = i+1; j < COL; j++) {
            if (mat[i][j]) {
                sum = calc_profit(j, job[i]);
                if (debug) {
                    printf("max profit for i %d is %d\n", i, sum);
                    getchar();
                }
                if (max_profit < sum) {
                    max_profit = sum;
                }
            }
        }
    }
    printf("Max Profit %d\n", max_profit);
    return 0;
}
