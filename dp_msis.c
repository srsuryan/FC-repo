/*
 * Given an array of n positive integers. Write a program to find the sum of maximum sum subsequence of the given array 
 * such that the intgers in the subsequence are sorted in increasing order. For example, if input is {1, 101, 2, 3, 100, 4, 5}, 
 * then output should be 106 (1 + 2 + 3 + 100), if the input array is {3, 4, 5, 10}, then output should be 22 (3 + 4 + 5 + 10) 
 * and if the input array is {10, 5, 4, 3}, then output should be 10
 */

#include <stdio.h>

int
msincsub (int *arr, int max)
{
   int i, j, maxsum = -1;
   int dp[32];
 
   for (i = 0; i < max; i++) {
   	dp[i] = arr[i];
   }

   for (i = 1; i < max; i++) {
       for (j = 0; j < i; j++) {

		if (arr[i] > arr[i-1]) {
		    dp[i] += dp[i-1];
		    if (maxsum < dp[i]) {
		  	maxsum = dp[i];
		    }
		    break;
		}
  	 
	        if (arr[i] > arr[j]) {
		    dp[i] += dp[j];
		}

		if (maxsum < dp[i]) {
		  maxsum = dp[i];
		}
 	}
    }
 
   return maxsum;
	
}


 
/* Driver program to test above function */
int main()
{
    int arr[] = {1, 101, 2, 3, 100, 4, 5};
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("Sum of maximum sum increasing subsequence is %d\n",
           msincsub( arr, n ) );
    return 0;
}

