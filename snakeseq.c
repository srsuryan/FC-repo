#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROW 4
#define COL 4

int debug = 0;

/*

Find maximum length Snake sequence

Given a grid of numbers, find maximum length Snake sequence and print it. If multiple snake sequences exists with the maximum length, print any one of them.

A snake sequence is made up of adjacent numbers in the grid such that for each number, the number on the right or the number below it is +1 or -1 its value. For example, if you are at location (x, y) in the grid, you can either move right i.e. (x, y+1) if that number is ± 1 or move down i.e. (x+1, y) if that number is ± 1.

For example,

9, 6, 5, 2
8, 7, 6, 5
7, 3, 1, 6
1, 1, 1, 7
*/
int mat[ROW][COL] = {
                  { 9, 6, 5, 2},
                  { 8, 7, 6, 5},
                  { 7, 3, 1, 6},
                  { 1, 1, 1, 7}
                };

void
walk_mat (int i, int j, int cmp, int *incseq, int inclen, 
	  int *outlen)
{
   int sseq[2][32], olen[2] = {0};
  
   memset(sseq[0], 0, sizeof(int)*32);
   memset(sseq[1], 0, sizeof(int)*32);

   if ((i >= ROW) || (i < 0))  return;
   if ((j >= COL) || (j < 0)) return;

   if ((mat[i][j] == (cmp-1)) ||
	(mat[i][j] == (cmp+1))) {
	memcpy(sseq[0], incseq, sizeof(int)*inclen);
        memcpy(sseq[1], incseq, sizeof(int)*inclen);
	sseq[0][inclen] = mat[i][j];
        sseq[1][inclen] = mat[i][j];
	olen[0] = inclen + 1;
	olen[1] = inclen + 1;
	if (debug) {
	    printf(" i %d j %d, val %d, cmp %d inclen %d n1 %d n2 %d\n",
			i, j, mat[i][j], cmp, inclen, sseq[0][0], sseq[1][1]);
	    getchar();
	}
	walk_mat(i+1, j, mat[i][j], sseq[0], inclen+1, &olen[0]);
	walk_mat(i, j+1, mat[i][j], sseq[1], inclen+1, &olen[1]);
  
	if (olen[0] > olen[1]) {
	    memcpy(incseq, sseq[0], sizeof(int)*olen[0]); 
	    *outlen = olen[0];	
	} else {
	    memcpy(incseq, sseq[1], sizeof(int)*olen[1]); 	
	    *outlen = olen[1];	
	}
   }  else {
	return;
   }

   //if ((i == ROW) && (j == COL)) return;

   return;
}

int
main ()
{
	int i = 0, j = 0, inclen = 0;
	int sseq[4][32], olen[4] = {0};

        for (i = 0; i < ROW; i++) {
	    memset(sseq[i], 0, sizeof(int)*32);
	}
        i = 0;
	while (i < ROW) {
		j = 0;
		while (j < COL) {
			inclen = 0;
			olen[j] = 1;
			sseq[j][0] = mat[i][j];
			//sseq[1][0] = mat[i][j];   	 
			walk_mat(i+1, j, mat[i][j], sseq[j], inclen+1, &olen[j]);     
			//walk_mat(i, j+1, mat[i][j], sseq[1], inclen+1, &olen[1]);     
			j++;
		}
		break;
		i++;
	}

	printf("Path %d %d \n", olen[0], olen[1]);
	j = 0;
	while (j < ROW) {
	    for (i = 0; i < olen[j]; i++) {
		 printf(" (%d)", sseq[j][i]);
	    }
	    j++;
	    printf("\n");	
	}
}

