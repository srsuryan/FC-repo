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
 
#define ROW 4
#define COL 4

int mat[ROW][COL] = {
                  { 9, 6, 5, 2},
                  { 8, 7, 6, 5},
                  { 7, 3, 1, 6},
                  { 1, 1, 1, 7}
                };

dir_td
getnxtp (int i, int j, int cycle)
{
   int cminrow, cmaxcol, cmaxrow, cmincol;   

  
   cminrow = cmincol = cycle;
   cmaxrow = ROW-cycle -1;
   cmaxcol = cmaxrow;
   
   if ((i == ROW/2) && (j == COL/2) && (i == cycle)) {
       return STOP;
   }

   if ((i == cmaxrow) && (j == cmincol)) {
       return UP;
   }

   if ((i == cminrow) && (j == cmaxcol)) {
       return DOWN;
   }
  
   if ((i == cmaxrow) && (j == cmaxcol)) {
       return LEFT;
   }

   if (i == cminrow) {
      return RIGHT;
   }

   if (i == cmaxrow) {
       return LEFT;
   }

   if (j == cmaxcol) {
       return DOWN;
   }

   if (j == cmincol) {
       return UP;
   }
   return STOP;
}

int 
main ()
{ 
  int i, j, cycle;
  dir_td pos;

  i = j = cycle = 0;

  while (1) {
      pos = getnxtp(i, j, cycle);
      if (pos != STOP) { 
      	  printf(" %d (%d %d) %s \n", mat[i][j], i, j, str[pos]);
          //getchar();
      }
      switch (pos) {
      case LEFT:
	 j--;
         break;
      case RIGHT:
         j++;
	 break;
      case DOWN:
         i++;
	 break;
      case UP:
         i--;
	 if ((j == i) && (i == cycle)) {
	     cycle++;
	     i = j = cycle;
	 }
	 break;
      case STOP:
         return STOP;
      default:
	 break;
      }
   }
   return STOP;
}
