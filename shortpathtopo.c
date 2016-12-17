#include <stdio.h>
#include <stdlib.h>
#include "qlib.h"


#define ROW 6
#define COL 6

#define INF 0xFF

static int debug = 1;
#if 0
int mat[ROW][4] = 
            {
                {INF, 1, 1, INF},
                {INF, INF, 1, INF},
                {1, INF, INF, 1},
                {INF, INF, INF, 1}
              };
#endif


int mat[ROW][COL] = {
                {INF, 5, 3, INF, INF, INF},
                {INF, INF, 2, 6, INF, INF},
                {INF, INF, INF, 7, 4, 2},
                {INF, INF, INF, INF, -1, 1},
                {INF, INF, INF, INF, INF, -2},
                {INF, INF, INF, INF, INF, INF}
                };

typedef struct node_ud_ {
    int i;
} node_ud;

int 
main ()
{
    int dist[COL], u, j;
    qelem_td *qelem;
    queue_td *q;
    node_ud *node;

    q = ts(0, mat, ROW, COL);
   
    for (j = 0; j < COL; j++) {
         dist[j] = INF;
    } 
    qelem = (node_td *)q->tail;    
    while (qelem) {
        node = (node_ud *)qelem->ptr;
        printf("TS_L :: %d ", node->i);
        qelem = (node_td *)qelem->prev;    
    }
    printf("\n");
    qelem = (node_td *)q->head;    
    u = node->i;
    dist[u] = 0;
    while (qelem) {
        node = (node_ud *)qelem->ptr;
        u = node->i;
        for (j = 0; j < COL; j++) {
             printf("u %d mat %x dist j %d u %d\n", u, mat[u][j], dist[j], dist[u]);
             if (mat[u][j] != INF) {
                 if (dist[j] > dist[u] + mat[u][j]) {
                     dist[j] = dist[u] + mat[u][j];
                     if (debug) {
                         printf(" %d -> %d cost %d\n", u, j, dist[j]);
                         getchar();
                     }
                 }
             }
        }
        qelem = qelem->next;
    }
    
    for (j = 0; j < COL; j++) {
         printf(" dist[%d] = %d \n", j, dist[j]); 
    } 
}
