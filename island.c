
#include <stdio.h>
#include <stdlib.h>

#define ROW 6
#define COL 6

#if 0
int mat[ROW][COL] = {
		  { 1, 0, 0, 0},
		  { 0, 0, 1, 1},
		  { 0, 0, 1, 1},
		  { 0, 1, 1, 0}
		};
int mat[ROW][COL] = {
		  { 0, 0, 0 },
		  { 1, 1, 0 },
		  { 1, 1, 0 },
		  { 0, 0, 1 },
		  { 0, 0, 1 },
		  { 1, 1, 0 },
		};
#endif
int
mat[ROW][COL] =  {
                {1, 0, 0, 0, 0, 0},
                {1, 0, 1, 1, 1, 1},
                {0, 0, 0, 0, 0, 0},
                {1, 1, 1, 0, 1, 1},
                {1, 1, 1, 0, 1, 1},
                {0, 0, 0, 0, 1, 1},
             };
int sto[ROW][COL] = {0};

void
walk_mat (int i, int j)
{

   if ((i >= ROW) || (i < 0))  return;
   if ((j >= COL) || (j < 0)) return;

   if (!mat[i][j]) return;
   if (sto[i][j]) return;

   sto[i][j] = 1;

   walk_mat(i+1, j); //down
   walk_mat(i, j+1); // right
   walk_mat(i-1, j); // up
   walk_mat(i, j-1); //left

   return;
}

int
main ()
{
 int i = 0, j = 0, island = 0;
   
  while (i < ROW) {
     j = 0; 
     while (j < COL) {
      	  if (mat[i][j] && !sto[i][j]) {
	      walk_mat(i, j);
	      island++;
      	  }
          j++;
       }
       i++;
  }

  printf(" Islands %d\n", island);
}
      
