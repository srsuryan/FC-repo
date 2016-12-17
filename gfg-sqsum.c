//http://www.geeksforgeeks.org/minimum-number-of-squares-whose-sum-equals-to-given-number-n/

#include <stdio.h>

int
min (int a, int b)
{
  if (a > b ) return a;
  return b;
}
 
// Returns count of minimum squares that sum to n
int getMinSquares(unsigned int n)
{
    // base cases
    if (n <= 3)
        return n;
 
    // getMinSquares rest of the table using recursive
    // formula
    int res = n; // Maximum squares required is n (1*1 + 1*1 + ..)
 
    // Go through all smaller numbers
    // to recursively find minimum
    for (int x = 1; x <= n; x++)
    {
        int temp = x*x;
        if (temp > n)
            break;
        else {
            printf("n %d res %d, temp %d\n", n, res, temp);
            getchar();
            res =  min(res, 1+getMinSquares(n - temp));
            printf("n2 %d res %d, temp %d\n", n, res, temp);
        }
    }
    return res;
}
 
// Driver program
int main()
{
    printf("Min SQ RT %d \n", getMinSquares(36));
    return 0;
}
