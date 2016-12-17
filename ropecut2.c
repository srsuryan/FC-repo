#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * Given a rope of length n meters, cut the rope in different parts of integer 
 * lengths in a way that maximizes product of lengths of all parts. You must make at 
 * least one cut. Assume that the length of rope is more than 2 meters.
 */

int dp[32] = {0};

int 
max (int a, int b) 
{
    if (a > b) return a;
    return b;
}

int 
best_cut (int i)
{
    int smax = i, j;

    for (j = 1; j < i; j++) {
         smax = max(smax, dp[i - j]*dp[j]);
         printf("i %d smax %d %d %d\n", i, smax, dp[i-j], dp[j]); 
    }

    dp[i] = smax;
    return smax;
}

int
main (int argc, char *argv[])
{
   int i;

   dp[1] = 1;
   dp[2] = 2;

   for (i = 3; i <= 10; i++) {
        printf("dp[%d] = %d ", i, best_cut(i));
    }

}

