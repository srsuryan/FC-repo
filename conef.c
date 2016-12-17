#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A Dynamic programming based C++ program to find number of
// non-negative solutions for a given linear equation
// Returns counr of solutions for given rhs and coefficients
// coeff[0..n-1]
int countSol(int coeff[], int n, int rhs)
{
    // Create and initialize a table to store results of
    // subproblems
    int dp[rhs+1];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
 
    // Fill table in bottom up manner
    for (int i=0; i<n; i++) {
      for (int j=coeff[i]; j<=rhs; j++) {
         dp[j] += dp[j-coeff[i]];
         printf("dp %d coeff %d j %d j-coeff %d\n ", dp[j], coeff[i], j, j - coeff[i]);
         getchar();
       }
    }  
 
    return dp[rhs];
}
 
// Driver program
int main()
{
    int coeff[]  = {2, 2, 5};
    int rhs = 4;
    int n = sizeof(coeff)/sizeof(coeff[0]);
    cout << countSol(coeff, n, rhs);
    return 0;
}
