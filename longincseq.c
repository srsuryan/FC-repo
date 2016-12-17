#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* LIS
 * http://www.geeksforgeeks.org/dynamic-programming-set-3-longest-increasing-subsequence/
 */

int dp[32] = {0};

int 
liseq (int a[], int max)
{
    int dp_max = 0, i, j, k, sum;

    for (i = 0; i < 32; i++) {
        dp[i] = 1;
    }

    for (i = 1; i < max; i++) {
        j = i;
        k = j - 1;
        while (k >= 0) {
            if (a[j] > a[k]) {
                sum = dp[k] + 1;
                if (sum > dp[j]) {
                    dp[j] = sum;
                    if (dp[j] > dp_max) {
                        dp_max = dp[j];
                        printf("a[%d] %d dp_max %d j dp[%d] = %d\n", j, a[j], dp_max, j, dp[j]);
                        break;
                    }
                }
            }
            k--;
        }
    }
    return dp_max;
}

int
main ()
{
    int sto[32] = {0}, j;
    int a[] = {10, 22, 9, 33, 21, 50, 41, 60, 80};
    //int a[] = {10, 22, 9, 33, 21, 23, 24, 25, 28, 30, 50, 41, 60, 80};
    int max = sizeof(a)/sizeof(int), lis;

    lis = liseq(a, max);
    for (j = max; j >= 0; j--) {
         sto[dp[j] -1] = a[j];  
    }

    j = 0;
    while (j <= max) {
       printf("sto[%d] = %d \n", j, sto[j]); 
       j++;
    }

    printf("liseq %d\n", lis);
}
