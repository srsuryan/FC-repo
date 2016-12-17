#include <stdio.h>
/*
 * Minimum number of jumps to reach end
 *                 1 2   3  
 * Input: arr[] = {1, 3, 5, 8, 9, 2, 6, 7, 6, 8, 9}
 * Output: 3 (1-> 3 -> 8 ->9)
 */

int
dp_jump (int *arr, int max)
{
   int i, j, dp[32] = {0};

   for (i = 0; i < max; i++)
        dp[i] = 0xFFFFF;
  
   dp[0] = 1;
   for (i = 1; i < max; i++) {
        for (j = 0; j < i; j++) {
	    if (j + arr[j] >= i) {
                if (dp[i] > (dp[j]+1)) {
	            dp[i] = dp[j]+1;
		}
	    }
	}
    }  

    for (i = 0; i < max; i++) 
	printf("dp[%d] = %d \n", i, dp[i]);
    return dp[max-1];
}

// Driver program to test above function
int main()
{
  int arr[] = {1, 3, 6, 3, 2, 3, 6, 8, 9, 5};
  int n = sizeof(arr)/sizeof(arr[0]);
  printf("Minimum number of jumps to reach end is %d ", dp_jump(arr, n-1));
  return 0;
}
