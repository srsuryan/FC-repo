// A Dynamic Programming based solution for 0-1 Knapsack problem
#include<stdio.h>

int debug = 1; 
int K[32][32];
// A utility function that returns maximum of two integers
int max(int a, int b) { return (a > b)? a : b; }
 
// Returns the maximum value that can be put in a knapsack of capacity W
int knapSack(int W, int wt[], int val[], int n)
{
   int i, w;
 
   // Build table K[][] in bottom up manner
   for (i = 0; i <= n; i++)
   {
       for (w = 0; w <= W; w++)
       {
           if (i==0 || w==0)
               K[i][w] = 0;
           else if (wt[i-1] <= w) {
                 K[i][w] = max(val[i-1] + K[i-1][w-wt[i-1]],  K[i-1][w]);
                 if (debug) {
                     printf("K[%d][%d] = %d  W-wt[i-1] = %d ", i, w, K[i][w], W-wt[i-1]);
                     getchar();
                 }
           } else {
                 K[i][w] = K[i-1][w];
           }
       }
   }
 
   return K[n][W];
}
 
int main()
{
    //int val[] = {60, 100, 120};
    //int wt[] = {10, 20, 30};
    int val[] = {10, 4, 7, 18, 12, 31};
    int wt[] = {1, 3, 4, 5, 7, 10};
    int  W = 12;
    int n = sizeof(val)/sizeof(val[0]), i, w;
   
    printf("%d\n", knapSack(W, wt, val, n));
   for (i = 0; i <= n; i++)
   {
       for (w = 0; w <= W; w++)
       {
            printf(" %2d ",K[i][w]); 
       }
       printf("\n");
    }
    return 0;
}
