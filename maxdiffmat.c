#include <stdio.h>

#define ROW 5
#define COL 5

int mat[ROW][COL] = {
	     { 1, 2, -1, -4, -20 },
             { 10, -3, 4, 2, 1 }, 
             { 3, 8, 6, 1, 3 },
             { -4, -1, 1, 7, -6 },
             { 0, -4, -8, -5, 1 }
	    };
int
main ()
{
   int i, j, smaxi, smini, smaxj, sminj, highest;
   int maxdiff = -1, lowest;

    smaxi = 4;
    smini = 1;
    smaxj = 2;
    sminj = 0;
    for (i = smaxi; i >= smini; i--) {
        for (j = smaxj+1; j >= sminj; j--) {
	     if (highest < mat[i][j]) {
	         highest = mat[i][j];
	     } else {
		  lowest = mat[i][j];
		  if (highest - lowest > maxdiff) {
		      maxdiff = highest - lowest;
		  }
	     }
	}
    }
 
    printf("maxdiff %d \n", maxdiff);
}	
