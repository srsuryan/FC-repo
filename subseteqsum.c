
// A Dynamic Programming solution for subset sum problem
#include <stdio.h>
 
// Returns 1 if there is a subset of set[] with sun equal to given sum
int 
isSubsetSum(int set[], int n, int sum)
{
    // The value of subset[i][j] will be 1 if there is a 
    // subset of set[0..j-1] with sum equal to i
    int subset[sum+1][n+1];

    // If sum is 0, then answer is 1
    for (int i = 0; i <= n; i++)
        subset[0][i] = 1;

    // If sum is not 0 and set is empty, then answer is 0
    for (int i = 1; i <= sum; i++)
        subset[i][0] = 0;

    // Fill the subset table in botton up manner
    for (int i = 1; i <= sum; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            subset[i][j] = subset[i][j-1];
            if (i >= set[j-1]) {
                subset[i][j] = subset[i][j] || 
                    subset[i - set[j-1]][j-1];
                printf(" subset[%d][%d] = %d set[%d] = %d subset[%d][%d] = %d", 
                        i, j, subset[i][j], j-1, set[j-1], 
                        i -set[j-1], j-1, subset[i-set[j-1]][j-1]);
                getchar();
            }
        }
    }

    // uncomment this code to print table
    for (int i = 0; i <= sum; i++)
    {
        for (int j = 0; j <= n; j++)
            printf ("%4d", subset[i][j]);
        printf("\n");
    } 

    return subset[sum][n];
}
 
// Driver program to test above function
int main()
{
  int set[] = {3, 34, 4, 12, 5, 2};
  int sum = 9;
  int n = sizeof(set)/sizeof(set[0]);
  if (isSubsetSum(set, n, sum) == 1)
     printf("Found a subset with given sum");
  else
     printf("No subset with given sum");
  return 0;
}
