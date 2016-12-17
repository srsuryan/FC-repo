#include <stdio.h>
#include <stdlib.h>
#include "qlib.h"


#define ROW 4
#define COL 4

#define INF 0xFF

static int debug = 1;

int mat[ROW][COL] = {
                     {INF, 3, 10, INF},
                     {INF, INF, INF, 6},
                     {INF, INF, INF, 7},
                     {2, INF, INF, INF},
                };

typedef struct node_ud_ {
    int i;
} node_ud;

typedef struct dist_td_ {
    int val[32];
    int idx;
    int ec;
} dist_td;

dist_td dist[32];

int 
main ()
{
    int u, j, ec, nec, i;
    qelem_td *qelem;
    queue_td *q;
    node_ud *node;

    q = ts(0, mat, ROW, COL);
#if 1  
    for (j = 0; j < COL; j++) {
         for (i = 0; i < 32; i++) {
            dist[j].val[i] = INF;
         }
         //dist[j].idx = 0;
         dist[j].ec = 0;
    }
#endif
    qelem = (qelem_td *)q->tail;    
    while (qelem) {
        node = (node_ud *)qelem->ptr;
        printf("TS_L :: %d ", node->i);
        qelem = (node_td *)qelem->prev;    
    }
    printf("\n");
    qelem = (qelem_td *)q->head;    
    u = node->i;
    dist[u].val[0] = 0;
    i = 0;
    while (qelem) {
        node = (node_ud *)qelem->ptr;
        u = node->i;
        for (j = 0; j < COL; j++) {
            printf("u %d mat %x dist j %d u %d\n", u, mat[u][j], dist[j].val[0], dist[u].val[0]);
            if (mat[u][j] != INF) {
                ec = dist[u].ec;
                nec = ec + 1;
                //while (i < dist[u].idx) {
                    if (dist[j].val[nec] > dist[u].val[ec] + mat[u][j]) {
                        dist[j].val[nec] = dist[u].val[ec] + mat[u][j];
                        if (debug) {
                            printf(" %d -> %d cost %d nec %d\n", u, j, dist[j].val[nec], nec);
                            getchar();
                        }
                        //i++;
                      //  dist[j].idx++;
                        dist[j].ec = nec;
                  }
                //}
            }
        }
        qelem = qelem->next;
    }
    
    for (j = 0; j < COL; j++) {
         for (i = 0; i <= dist[j].ec; i++) {
             printf(" dist[%d] = %d val %d\n", j, dist[j].val[i]); 
         }
    } 
}
