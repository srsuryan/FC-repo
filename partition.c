
#include <stdio.h>
#include <stdlib.h>

/*
 * arr[] = {1, 5, 11, 5}
 * Output: 1 
 * The array can be partitioned as {1, 5, 5} and {11}
 *
 * arr[] = {1, 5, 3}
 * Output: false 
 * The array cannot be partitioned into equal sum sets.
 */

int dp[64] = {0};
int debug = 1;

int
partition_helper (int t, int i)
{
    int j, rv;

    while (i >= 1) {//j => 24(t) - 13 (i) = 11 (j) ; // 11 - 5 = 6
        if (dp[i]) {
            dp[i]--;
            j = t - i;
            
            if (debug) {
                printf("1.t %d i %d j %d\n", t, i, j);
            }
            
            if (dp[j]) {
                dp[j]--;
                if (debug) {
                    printf("2.t %d i %d j %d\n", t, i, j);
                }
                return 1;
            }
            rv = partition_helper(j, j-1);   
            if (rv) return rv; 
        }
        i--; 
    }
    return 0;
}

int
main ()
{
    //int a[] = {2, 2, 5, 5, 13, 6, 4, 1, 8, 2}, sum = 0;
    //int a[] = {5, 5, 1, 11};
    int a[] = {1, 2, 5};

    int sum = 0, i, n = sizeof(a)/sizeof(int);
   
    dp[0] = 0xFF; 
    for (i = 0; i < n; i++) {
         sum += a[i];
         dp[a[i]]++;
    }
   
    if (sum%2) {
        printf("Invalid\n");
    }

    if (dp[sum/2]) {
        printf("partition possible\n");
        return 1;
    }
    printf(" Partition possible  %s \n", partition_helper(sum/2, sum/2-1) ? "Yes" : "NO");

}
