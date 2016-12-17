#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define ROW 6
#define COL 6

enum {
   LEFT = 0,
   RIGHT,
   UP,
   DOWN,
};

#define XXX  'X'
#define OOO  'O'
#define MINUS  '-'
#define NOP '@'

int debug = 0;

char mat[ROW][COL] =  {
                     {'X', 'O', 'X', 'X', 'X', 'X'},
                     {'X', 'O', 'X', 'X', 'O', 'X'},
                     {'X', 'X', 'X', 'O', 'O', 'X'},
                     {'O', 'X', 'X', 'X', 'X', 'X'},
                     {'X', 'X', 'X', 'O', 'X', 'O'},
                     {'O', 'O', 'X', 'O', 'O', 'O'},
                    };
int
check_boundary (int i, int j)
{

    if ((i >= ROW) || (i < 0)) {
        return 0;
    }

    if ((j >= COL) || (j < 0)) {
        return 0;
    }

    return 1;
}

char
get_dir (int i, int j)
{
   int bcup, bcdn, bclft, bcrgt;
   char st;
   int flag = 0;

   bcup = check_boundary(i-1, j);
   bcdn = check_boundary(i+1, j);
   bclft = check_boundary(i, j-1);
   bcrgt = check_boundary(i, j+1);

   if (debug) {
        printf("%d %d %d %d\n", bcup, bcdn, bclft, bcrgt);
        getchar();
    }
   if (bcup) {
       st = mat[i-1][j];
       if (st == XXX) {
           flag |= 1 << UP;
       } else if (st == OOO) {
           return NOP;
       } else if (st == MINUS) {
           /* Nothing to do */
       }
    } else {
        return NOP;
    }

    if (bclft) {
        st = mat[i][j-1];
        if (st == XXX) {
            flag |= 1 << LEFT;
        } else if (st == OOO) {
            return NOP;
        } else if (st == MINUS) {
            /* Nothing to do */
        }
    } else {
        return NOP;
    }

    if (bcdn) {
        st = mat[i+1][j];
        if (st == XXX) {
            flag |= 1 << DOWN;
        } else {
            /* Do nothing */
        }
    } else {
        return NOP;
    }
    
    if (bcrgt) {
        st = mat[i][j+1];
        if (st == XXX) {
            flag |= 1 << RIGHT;
        } else {
        }
    } else {
        return NOP;
    }

    if (debug) {
        printf(" RET flag %x %d %d %c\n",  flag, i, j, mat[i][j]);
        //getchar();
    }
 
    /* All 4 sides are sorrounded by 'X', convert 'O' to 'X' */
    if (flag == 0xF) {
        return XXX;
    }

    if (flag == 0x7) {
        printf(" Return MINUS  %d %d %c\n", i, j, mat[i][j]);
        //getchar();
    }

    return MINUS;
}


void
first_pass (int i, int j)
{
    char dir;

    if (!check_boundary(i,j)) {
        return;
    }

    dir = get_dir(i,j);

    switch (dir) {
    case MINUS:
        mat[i][j] = '-';
        if (debug) {
            printf("(%d %d ) minus %c \n", i, j, mat[i][j]);
            getchar();
        }
        break;
    case XXX:
        mat[i][j] = 'X';
        if (debug) {
            printf("(%d %d ) XXX %c \n", i, j, mat[i][j]);
            //getchar();
        }
        break;
    case OOO:
        mat[i][j] = 'O';
        break;
    default:
        if (debug) {
            printf("(%d %d) dir %c \n",i, j, dir);
            getchar();
        }
        break;
    }
}

void
second_pass (int i, int j) 
{
    char dir, str, std;

    if (!check_boundary(i, j)) {
        dir = OOO;
    } else {
        str = mat[i][j+1];
        std = mat[i+1][j];
        if ((str == XXX) && 
                (std == XXX)) {
            mat[i][j] = 'X';
        } else {
            mat[i][j] = 'O';
        }
    }
#if 0
    switch (dir) {
    case MINUS:
        mat[i][j] = '-';
        break;
    case XXX:
        mat[i][j] = 'X';
        break;
    case OOO:
        mat[i][j] = 'O';
        break;
    default:
        if (debug) {
            printf("(%d %d) dir %s \n",i, j, str_dir[dir]);
            getchar();
        }
        break;
    }
#endif
}

int
main (int argc, char *argv[])
{
    int i, j;

    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            if ((i == 0) && (j == 1)) {
                 debug = 1;
                printf(" OOO %d %d %c\n", i, j, OOO); 
            }
            if (mat[i][j] == OOO) {
                first_pass(i, j);
            }
            debug = 0;
        }
    }
    
    for (i = ROW-2; i >= 1; i--) {
        for (j = COL-2; j >= 1; j--) {
            if (mat[i][j] == MINUS) {
                printf("%d %d %c \n", i, j, mat[i][j]);
                getchar();
                second_pass(i, j);
            }
        }
    }
    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
             printf("mat[%d][%d] = %c ", i, j, mat[i][j]);
        }
        printf("\n");
    }
}
