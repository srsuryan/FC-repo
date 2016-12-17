#include <stdio.h>

#define ROW 2
#define COL 2

int a[ROW][COL] =
 	       {	
		 {1, 2},
		 {3, 4}
		};
int b[ROW+COL][ROW+COL];

int debug  = 1;

void
send_prn (int i, int j, int row, int col)
{
	int k, l, scol = col;

	for (l = 0; l <ROW; l++) {
		for (k = 0; k < COL; k++) {
			b[row][col] = a[i][j]*a[l][k];
			if (debug) {
				printf("row %d col %d a %d b %d\n", row, col, a[i][j], a[l][k]);
				getchar();
			}
			col++;
		}
		col = scol;
		row++;
	}
}


int 
main ()
{
   int row, col, i, j;
   row = col = -1;

   for (i = 0; i < ROW; i++) {
     row++;
     col++;
     col = col%(COL+ROW);	
     for (j = 0; j < COL; j++) {
	  send_prn(i, j, row, col); //a, b
	  col = col + COL;
     }
     col  = col -1;
     row = row + ROW -1;
   }	     

   for (i = 0; i < ROW+COL; i++) {
	for (j = 0; j < ROW+COL; j++) {
	   printf(" [%d] ", b[i][j]);
        }
	printf("\n");
   }
}
