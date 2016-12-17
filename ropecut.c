#include <stdio.h>
#include <stdlib.h>

int debug = 1;

int
max (int a, int b, int c)
{

    if (a > b) {
        if (a > c) return a;
        return c;
    } else if (b > c) {
        return b;
    }
    return c;
    
}

// A Dynamic Programming solution for Max Product Problem
int maxprod (int n)
{
   int val[n+1];
   val[0] = val[1] = 0;
  
   // Build the table val[] in bottom up manner and return
   // the last entry from the table
   for (int i = 1; i <= n; i++)
   {
      int max_val = 0;
      for (int j = 1; j <= i/2; j++) {
         if (debug) {
             printf(" mv %d i %d j %d val %d\n", max_val, i, j, val[i-j]);
             getchar();
         }
         max_val = max(max_val, (i-j)*j, j*val[i-j]);
      }
      val[i] = max_val;
   }
   return val[n];
}

int
main (int argc, char *argv[])
{
   printf(" main %d\n", maxprod(strtol(argv[argc-1], 0, 0)));
}
