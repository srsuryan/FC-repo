#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ROW 3
#define COL 3

int mat[ROW][COL] = {
                     {1, 2, 3},
                     {4, 5, 6},
                     {7, 8, 9},
                    };

typedef enum dir_td_ {
    LEFT = 0,
    RIGHT,
    UP,
    DOWN,
    STOP,
    INVALID,
} dir_td;

int start = 1;

dir_td
next_dir (int i, int j, dir_td prev)
{
   static int si, sj;

   if (start) {
       si = i;
       sj = j;
       start = 0;
   } else {
       if ((i == si) && (j == sj)) {
           return STOP;
       }
   }

   if ((i >= ROW) || (i < 0)) {
       return INVALID;
   }
   
   if ((j >= COL) || (i < 0)) {
       return INVALID;
   }

   switch (prev) {
   case UP:
       i--;
       if (i == -1) {
           return RIGHT;
       }
       return UP;
       break;
   case DOWN:
       i++;
       if (i == ROW) {
           return LEFT;
       }
       return DOWN;
       break;
   case LEFT:
       j--;
       if (j == -1) {
           return UP;
       }
       return LEFT;
       break;
   case RIGHT:
       j++;
       if (j == COL) {
           return DOWN;
       }
       return RIGHT;
       break;
    default:
       return INVALID;
   }
}


int
main (int argc, char *argv[])
{
    int i, j, p, n;
    dir_td dir, prev = RIGHT;

    p = mat[0][0];
    i = j = 0;
    while (1) {
        dir = next_dir(i, j, prev);
        switch (dir) {
            case UP:
                i--;
                n = mat[i][j];
                mat[i][j] = p;
                p = n;
                prev = UP;
                break;
            case DOWN:
                i++;
                n = mat[i][j];
                mat[i][j] = p;
                p = n;
                prev = DOWN;
                break;
            case LEFT:
                j--;
                n = mat[i][j];
                mat[i][j] = p;
                p = n;
                prev = LEFT;
                break;
            case RIGHT:
                j++;
                n = mat[i][j];
                printf("RIGHT %d %d n %d p %d", i, j, n, p);
                getchar();
                mat[i][j] = p;
                p = n;
                prev = RIGHT;
                break;
            default:
                if (dir == INVALID) {
                    printf("%d %d invalid \n", i, j);
                    return -1;
                }
                break;
        }
        if (dir == STOP) break;
    }

    if (dir == STOP) {
        for (i = 0; i < ROW; i++) {
            for (j = 0; j < COL; j++) {
                printf("mat[%d][%d] = %d ", i, j, mat[i][j]);
            }
            printf("\n");
        }
    }
}
