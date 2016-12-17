#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "qlib.h"

#define ROW 6
#define COL 5

static int debug = 1;

int mat[ROW][COL] = {
                       {0, 1, 1, 0, 1},
                       {1, 1, 0, 1, 0},
                       {0, 1, 1, 1, 0},
                       {1, 1, 1, 1, 1},
                       {1, 1, 1, 1, 1},
                       {0, 0, 0, 0, 0},
                    };
int
get_bot_row ()
{
    int a[32] = {0};
    int i, j, opt;

    for (i = ROW-1; i > 0; i--) {
        opt = 0;
        for (j = 0; j < COL; j++) {
             if (mat[i][j]) {
                 opt++;
             }
        }
        if (opt == COL) return i;
    }

    if (debug) {
        for (i = 0; i < ROW; i++) {
             printf(" (a[%d] = %d) ", i, a[i]);
        }
    }
    printf("\n");
    return find_min(a, ROW);
}

int
get_top_row (int maxrow, int startrow)
{
    int *flags, i, j;
    int a[32] = {0};

    flags = calloc(1, maxrow*sizeof(int));

    for (j = 0; j < COL; j++) {   
        for (i = startrow; i >= 0; i--) {
            if (!mat[i][j]) {
                flags[j] = 1;
                a[j] = i;
            } else {
                if (flags[j]) {
                    break;
                } 
                a[j] = i;
            }     	
        }
    }
    if (debug) {
        for (i = 0; i < maxrow; i++) {
            printf(" (a[%d] = %d) ", i, a[i]);
        }
    }
    printf("\n");
    return find_max(a, maxrow);
}

int*
get_hist (int topr, int botr)
{
    int *a, i, j;

    a = calloc(1, sizeof(int)*COL);
    for (i = topr; i <= botr; i++) {
         for (j = 0; j < COL; j++) {
              if (mat[i][j]) {
                  a[j]++;
              }
         }
    }
    return a;
}

int
main (int argc, char *argv[])
{
     int botrow, toprow, *a, j;

     //botrow = get_bot_row();
     toprow = get_top_row(ROW, ROW-1);
     toprow = get_top_row(ROW, botrow-1);

     printf("Get bottom row %d top row %d\n", botrow, toprow);
    
     a = get_hist(toprow, botrow);
     for (j = 0; j< COL; j++) {
          printf(" (a[%d] = %d) \n", j, a[j]);     
     }
     printf("largest rect %d\n", largestrect(a, COL));
}

