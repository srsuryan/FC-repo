#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ROW 5
#define COL 5
typedef enum dir_td_ {
    LEFT = 0,
    RIGHT,
    INVALID,
} dir_td;

int debug = 1;

int mat[ROW][COL] = {
                        {'E', 'C', 'C', 'C', 'C'},
                        {'C', '#', 'C', '#', 'E'},
                        {'#', 'C', 'C', '#', 'C'},
                        {'C', 'E', 'E', 'C', 'E'},
                        {'C', 'E', '#', 'C', 'E'},
                    };

int 
check_boundary (int i, int j)
{

    if ((i < 0) || (i >= ROW)) {
        return 1;
    }

    if ((j < 0) || (j >= COL)) {
        return 1;
    }
    return 0;
}


dir_td
toggle (dir_td dir)
{
    switch(dir) {
    case LEFT:
        return RIGHT;
    case RIGHT:
        return LEFT;
    default:
        break;
    }
    return INVALID;
}

void
cc (int i, int j, dir_td dir, int *count)
{
    int ac = 0, dc = 0;

    if (check_boundary(i, j)) {
        return;
    }

    if (mat[i][j] == 'C') {
        (*count)++;
    }


    if (mat[i][j] == '#') {
        return; 
    }

    if (debug) {
        printf("i %d j %d dir %d count %d\n", i, j, dir, *count);
        getchar();
    }

    if (dir == LEFT) {
        cc(i, j-1, LEFT, &ac);
    } else {
        cc(i, j+1, RIGHT, &ac);
    }

    cc(i+1, j, dir^dir, &dc);

    if (dc > ac) {
        *count = dc + *count;
    } else {
        *count = ac + *count;
    }
}

int
main (int argc, char *argv[]) 
{
    int ac, dc;

    ac = dc = 0;
    cc(0, 1, RIGHT, &ac);
    cc(1, 0, dir^dir, &dc);
    
    printf(" count1 %d count2 %d\n", ac, dc);
}

