/* At most k path to reach final destination */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define ROW 3
#define COL 3

int debug = 0;
typedef enum dir_td_ {
    DOWN = 0,
    RIGHT,
    MAX_DIR,
} dir_td;

typedef enum path_td_ {
    NO_T = 0,
    SINGLE_T,
    DOUBLE_T,
    MAX_T,
} path_td;

#define MAX_DIR 2
#define MAX_PATH 3

int pd[MAX_DIR][MAX_T] = {0};

int mat[ROW][COL] = {
                       {1, 2, 3},
                       {4, 5, 6},
                       {7, 8, 9}
                    };

typedef struct storage_ {
        int pd[MAX_DIR][MAX_T];
} storage;

storage sto[ROW][COL] = {0};

void
assign_val (int i, int j, dir_td dir)
{
    sto[i][j].pd[dir][NO_T] += pd[dir][NO_T];
    sto[i][j].pd[dir][SINGLE_T] += pd[dir][SINGLE_T];
    sto[i][j].pd[dir][DOUBLE_T] += pd[dir][DOUBLE_T];
}

void
get_path_det (int i, int j, dir_td dst_dir)
{
    if (dst_dir == DOWN) {
        pd[DOWN][NO_T] = sto[i][j].pd[DOWN][NO_T];
        pd[DOWN][SINGLE_T] = sto[i][j].pd[DOWN][SINGLE_T];
        pd[DOWN][DOUBLE_T] = sto[i][j].pd[DOWN][DOUBLE_T];
        if (sto[i][j].pd[RIGHT][NO_T]) {
            pd[DOWN][SINGLE_T] = sto[i][j].pd[RIGHT][NO_T];
        }
        if (sto[i][j].pd[RIGHT][SINGLE_T]) {
            pd[DOWN][DOUBLE_T] = sto[i][j].pd[RIGHT][SINGLE_T];
        }
    }
    if (dst_dir == RIGHT) {
        pd[RIGHT][NO_T] = sto[i][j].pd[RIGHT][NO_T];
        pd[RIGHT][SINGLE_T] = sto[i][j].pd[RIGHT][SINGLE_T];
        pd[RIGHT][DOUBLE_T] = sto[i][j].pd[RIGHT][DOUBLE_T];
        if (sto[i][j].pd[DOWN][NO_T]) {
            pd[RIGHT][SINGLE_T] = sto[i][j].pd[DOWN][NO_T];
        }
        if (sto[i][j].pd[DOWN][SINGLE_T]) {
            pd[RIGHT][DOUBLE_T] = sto[i][j].pd[DOWN][SINGLE_T];
        }
    }
}

int
main (int argc, char *argv[])
{
    int i, j, a[6], b = 0;

    for (i = 0; i < ROW; i++) {
         sto[i][0].pd[DOWN][NO_T] = 1;
    }
    
    for (j = 0; j < COL; j++) {
         sto[0][j].pd[RIGHT][NO_T] = 1;
    }

    for (i = 1; i < ROW; i++) {
        for (j = 1; j < COL; j++) {
            memset(pd, 0, sizeof(int)*MAX_DIR*MAX_PATH);
            get_path_det(i-1, j, DOWN);
            assign_val(i, j, DOWN);
            if (debug) {
                printf(" (%d, %d), DOWN (%d %d) (%d %d) (%d %d)\n", i, j,
                        pd[RIGHT][NO_T], pd[DOWN][NO_T],
                        pd[RIGHT][SINGLE_T], pd[DOWN][SINGLE_T],
                        pd[RIGHT][DOUBLE_T], pd[DOWN][DOUBLE_T]);
                getchar();
            }
            memset(pd, 0, sizeof(int)*MAX_DIR*MAX_PATH);
            /* Now for LEFT COMP */
            get_path_det(i, j-1, RIGHT);
            assign_val(i, j, RIGHT);
            if (debug) {
                printf(" (%d, %d), RIGHT (%d %d) (%d %d) (%d %d)\n", i, j,
                        pd[RIGHT][NO_T], pd[DOWN][NO_T],
                        pd[RIGHT][SINGLE_T], pd[DOWN][SINGLE_T],
                        pd[RIGHT][DOUBLE_T], pd[DOWN][DOUBLE_T]);
                getchar();
            }
        }
    }

     a[0] = sto[ROW-1][COL-1].pd[DOWN][NO_T];
     a[1] = sto[ROW-1][COL-1].pd[DOWN][SINGLE_T];
     a[2] = sto[ROW-1][COL-1].pd[DOWN][DOUBLE_T];
     
     a[3] = sto[ROW-1][COL-1].pd[RIGHT][NO_T];
     a[4] = sto[ROW-1][COL-1].pd[RIGHT][SINGLE_T];
     a[5] = sto[ROW-1][COL-1].pd[RIGHT][DOUBLE_T];
     for (i = 0; i < 6; i++) {
          b += a[i];
     }

    printf("Total path with utmost 2 direction change are (%d %d %d %d %d %d) = %d\n",
            a[0], a[1], a[2], a[3], a[4], a[5], b);
}

