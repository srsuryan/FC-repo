#include <stdio.h>
#include <stdlib.h>
#include "qlib.h"


#define ROW 4
#define COL 4

#define INF 0xFFFFFF

static int debug = 0;
#if 0
int mat[ROW][4] = 
            {
                {0, 1, 1, INF},
                {INF, 0, 1, INF},
                {1, INF, 0, 1},
                {INF, INF, INF, 1}
              };

int mat[ROW][COL] = {
                {0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0},
                {0, 0, 0, 1, 0, 0},
                {0, 1, 0, 0, 0, 0},
                {1, 1, 0, 0, 0, 0},
                {1, 0, 1, 0, 0, 0}
                };
#endif


int visited[ROW] = {0};

typedef struct node_ud_ {
    int i;
} node_ud;


void
dfshelper (int r, int fd, int mat[][COL], int *count)
{
    node_ud *node;
    int j;

    node = (node_ud *)calloc(1, sizeof(node_ud));
    node->i = r;
    visited[r] = 1;
    (*count)++;
    qpush(fd, (void *)node);
    
    for (j = 0; j < COL; j++) {
         if (mat[r][j] && mat[r][j] != INF && !visited[j]) {
             dfshelper(j, fd, mat, count);
        }
    }
}


void 
tshelper (int r, int fd,  int mat[][COL], int *count, int mc) 
{
    node_ud *node;
    int j;

    visited[r] = 1;
    (*count)++;

    if (debug) {
        printf(" r = %d count %d\n", r, *count);
        getchar();
    }

    node = (node_ud *)calloc(1, sizeof(node_ud));
    node->i = r;
    
    for (j = 0; j < mc; j++) {
         if (!visited[j] && mat[r][j] && mat[r][j] != INF) {
             printf("mat[%d][%d] = %d \n", r, j, mat[r][j]);
             tshelper(j, fd, mat, count, mc);
         }
    }

    if (debug) {
        printf(" Push %d, count %d\n", r, *count);
        getchar();
    }
    qpush(fd, (void *)node);
}

queue_td * 
ts (int start, int mat[][COL], int mr, int mc)
{
    int rv, j, i, count = 0, fd;
    node_ud *node;
    queue_td *q;

    rv = lib_init(QUEUE, &q, &fd);
    if (!rv || !q) {
        printf("Lib init failed %d %p\n", rv, q);
        return NULL;
    }

    i = start;
    while (count < mr) {
        if (!visited[i]) {    
            tshelper(i, fd, mat, &count, mc);
        }
        if (count < mr) {
            i = (i+1)%mr;
        }
    }

    if (debug) {
        node = (node_ud *)qpop(fd);
        while (node) {
            printf("TS :: %d ", node->i);
            node = (node_ud *) qpop(fd);
        }    
        printf("\n");    
    }
    
    return q;
}


void
dfs (int start, int mat[][COL])
{
    int i, j, rv, fd, count = 0;
    node_ud *node;
    queue_td *q;

    rv = lib_init(QUEUE, &q, &fd);
    if (!rv || !q) {
        printf("Lib init failed %d %p\n", rv, q);
        return;
    }

    i = start;
    while (count < ROW) {
        if (!visited[i]) {
            node = (node_ud *)calloc(1, sizeof(node_ud));
            node->i = i;
            visited[i] = 1;
            count++;
            qpush(fd, (void *)node);
            for (j = 0; j < COL; j++) {
                if (mat[start][j] && mat[start][j] != INF && !visited[j]) {
                    dfshelper(j, fd, mat, &count);
                }
            }
        }
        if (count < ROW) {
            i = (i+1)%ROW;
        }
        /* Lets check if all nodes are visited */
    }

    node = (node_ud *)qpop(fd);
    while (node) {
        printf("DFS :: %d ", node->i);
        node = (node_ud *) qpop(fd);
    }    

    printf("\n");    
}


#if 0
int 
main (int argc, char *argv[])
{
   int start, alg;

   if (argc <= 2) return 1;

   start = strtol(argv[1], 0, 0);
   alg = strtol(argv[2], 0, 0);

   if (alg == 1) {
       dfs(start, mat);
   } else {
        ts(start, mat, ROW, COL);
   }
}
#endif
