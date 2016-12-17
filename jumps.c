#include <stdio.h>

int dp[32];

void jump (int *a, int max)
{
    int j, p, dst;

    for (j = 1; j < max; j++) {
        p = j-1;//p = 2
        dst = a[p];//dst = 6
        while (dst) {
            if (dp[p+dst] > dp[p]+1) {
                dp[p+dst] = dp[p] +1;
            }
            dst--;
        }
    }
}

int 
main (int argc, char *argv[])
{
    int a[] = {1, 3, 6, 3, 2, 3, 6, 8, 9, 5};
    int i, n = sizeof(a)/sizeof(int);

    for (i = 0; i < n; i++) {
        dp[i] = 0xFF;
    }
    dp[0] = 0;
    jump(a, n);

    for (i = 0; i < n; i++) {
        printf("a[%d]= %d ", i, dp[i]);
    }
    printf("\n");
}

