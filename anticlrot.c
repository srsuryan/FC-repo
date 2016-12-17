#include <stdio.h>


typedef enum dir_ {
   NONE = 0,
   UP,
   DOWN,
   LEFT,
   RIGHT,
   STOP,
} dir_td;

char str[STOP+1][12] = { "None", "UP", "DOWN", "LEFT", "RIGHT", "STOP"};
int debug = 1;
 
#define ROW 3
#define COL 3
int cminrow = 0, cmaxrow = ROW -1;
int cmincol = 0, cmaxcol = COL -1;
 
int mat[ROW][COL] = {
                  { 1, 2, 3},
                  { 4, 5, 6},
                  { 7, 8, 9},
                };

dir_td
getnxtp (int i, int j)
{

   if ((i == cminrow) && (j == cmincol)) {
       return DOWN;
   }

   if ((i == cmaxrow) && (j == cmincol)) {
       return RIGHT;
   }
  
   if ((i == cmaxrow) && (j == cmaxcol)) {
       return UP;
   }

   if (i == cminrow) {
      return LEFT;
   }

   if ( i == cmaxrow) return RIGHT;

   if (j == cmaxcol) {
       return UP;
   }

   if (j == cmincol) {
       return DOWN;
   }
   return STOP;
}

int 
main ()
{ 
	int i, b = 0, j, k, move, pick, temp;
	dir_td pos;

	i = j = pick =0; 

	for (k = 0; k < COL-1; k++) {
		pick = mat[0][k];
		move = 0;
                b = 0;
		j = k;

		while (1) {
			move++;
			pos = getnxtp(i, j);
			if (debug) {
			    printf("[%d] G %s (%d %d) p %d t %d\n ", k, str[pos], i, j, pick, temp);
				//getchar();
			}
			switch (pos) {
				case LEFT:
					j--;
					if (move == ROW-1) {
						temp = mat[i][j];
						if (debug) {
						    printf("L (%d %d) p %d t %d ", i, j, pick, temp);
						    getchar();
						}
						mat[i][j] = pick;
						pick = temp;
					        move = 0;
					} else {
						//j--;
					}
					if ((i == 0) && (j == k)) {
						b = 1;
					}
					break;
				case RIGHT:
					j++;
					if (move == ROW-1) {
						temp = mat[i][j];
						if (debug) {
						    printf("R (%d %d) p %d t %d ", i, j, pick, temp);
						    getchar();
						}
						mat[i][j] = pick;
						pick = temp;
					        move = 0;
					} else {
						//j++;
					}
					if ((i == 0) && (j == k)) {
						b = 1;
					}
					break;
				case UP:
					i--;
					if (move == ROW-1) {
						temp = mat[i][j];
						if (debug) {
							printf("U (%d %d) p %d t %d ", i, j, pick, temp);
						    getchar();
						}
						mat[i][j] = pick;
						pick = temp;
					        move = 0;
					} else {
						//i--;
					}
					if ((i == 0) && (j == k)) {
						b = 1;
					}
					break;
				case DOWN:
					i++;
					if (move == ROW-1) {
						temp = mat[i][j];
						if (debug) {
							printf("D (%d %d) p %d t %d ", i, j, pick, temp);
						    getchar();
						}
						mat[i][j] = pick;
						pick = temp;
					        move = 0;
					} else { 
					     //i++;
					}
					if ((i == 0) && (j == k)) {
						b = 1;
					}
					break;
				default:
					break;
			}
			if (b) break;
		}      	
	} 

	for (i = 0; i < ROW; i++) {
		for (j = 0; j < COL; j++) {
			printf(" [%d] ", mat[i][j]);
		}
		printf("\n");
	}

}
