#include<stdio.h>
 
// A utility function that returns maximum of two integers
int max(int a, int b) { return (a > b)? a : b; }
 
// Returns the maximum value that can be put in a knapsack of capacity W
int knapSack(int K[][6], int W, int wt[], int val[], int n)
{
   int i, w;
 
   // Build table K[][] in bottom up manner
   for (i = 0; i <= n; i++)
   {
       for (w = 0; w <= W; w++)
       {
           if (i==0 || w==0) {
               K[i][w] = 0;
           } else if (wt[i-1] <= w) {
               printf(" wt[%d] = %d, w = %d, val[%d] %d + k[%d][%d] %d, k[%d][w=%d] = %d\n",
                        i-1, wt[i-1], w, i-1, val[i-1], i-1, w-wt[i-1], K[i-1][w-wt[i-1]], i-1, w, K[i-1][w] );
               K[i][w] = max(val[i-1] + K[i-1][w-wt[i-1]],  K[i-1][w]);
               printf("k[%d][w=%d] %d\n", i, w, K[i][w]);
              // getchar();
           } else {
               K[i][w] = K[i-1][w];
               printf("ELSE --- k[%d][w=%d] %d\n", i-1, w, K[i-1][w]);
               //getchar();
           }
       }
   }
 
   return K[n][W];
}
 
int main()
{
    int val[] = {60, 100, 120};
    int wt[] = {1, 2, 3};
    int W = 5, w, i;
    //int val[] = {10, 4, 7, 18, 12, 31};
    //int wt[] = {1, 3, 4, 5, 7, 10};
    int n = sizeof(val)/sizeof(val[0]);
   int K[n+1][W+1];
    
    printf("%d\n", knapSack(K, W, wt, val, n));
    for (i = 0; i <= n; i++) {
       for (w = 0; w <= W; w++) {
            printf("K[%d][%d] = %3d ", i, w, K[i][w]);
       }
       printf("\n");
    }
    return 0;
}
