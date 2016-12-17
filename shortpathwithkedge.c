#include <stdio.h>
#include <stdlib.h>
#include "qlib.h"


#define ROW 4
#define COL 4

#define INF 0xFF

static int debug = 0;

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
    int cnt;
} dist_td;

dist_td dist[32];

int
get_dist (dist_td dist[], int u, int *ind)
{
    int j;

    *ind = *ind + 1;
    for (j = *ind; j < 32; j++) {
        if (dist[u].val[j] != INF) {
            *ind = j;
            return j;
        }
    }   
    return -1;
}

int 
main ()
{
    int u, j, ec, nec, cec, i, ind;
    qelem_td *qelem;
    queue_td *q;
    node_ud *node;

    q = ts(0, mat, ROW, COL);
    for (j = 0; j < COL; j++) {
         for (i = 0; i < 32; i++) {
            dist[j].val[i] = INF;
         }
         dist[j].cnt = 0;
    }
    if (debug) {
        qelem = (qelem_td *)q->tail;    
        while (qelem) {
            node = (node_ud *)qelem->ptr;
            printf("TS_L :: %d ", node->i);
            qelem = (node_td *)qelem->prev;    
        }
        printf("\n");
    }
    qelem = (qelem_td *)q->head;    
    u = node->i;
    dist[u].val[0] = 0;
    dist[u].cnt = 1;
    i = 0;
    while (qelem) {
        node = (node_ud *)qelem->ptr;
        u = node->i;
        for (j = 0; j < COL; j++) {
            if (debug) {
                printf("u %d %d mat %x cnt %d\n", u, j, mat[u][j], dist[j].val[0], dist[u].cnt);
            }
            if (mat[u][j] != INF) {
                ind = -1;
                i = 0;
                  while (1) {
                    cec = get_dist(dist, u, &ind);//better to convert into LL, the soln becomes n^2*k
                    if (cec == -1) { break;}
                    nec = cec + 1;
                    if (debug) {
                        printf("u %d v %d, cec %d ind %d val %d\n", u, j, cec, ind, dist[u].val[ind]);
                    }
                    if (dist[u].val[ind] != INF) {
                        if (dist[j].val[nec] > dist[u].val[ind] + mat[u][j]) {
                            dist[j].val[nec] = dist[u].val[ind] + mat[u][j];
                            dist[j].cnt++;
                            if (debug) {
                                printf(" %d -> %d : [%d %d] : cost %d i %d cnt %d\n", u, j, cec, nec,
                                         dist[j].val[nec], i, dist[j].cnt);
                                getchar();
                            }
                        }
                    }
                    i++;
                }
            }
        }
        qelem = qelem->next;
    }

    printf("dist[3] %d %d %d \n", dist[3].val[0], dist[3].val[1], dist[3].val[2]); 
   
    for (j = 0; j < COL; j++) {
         for (i = 0; i <= dist[j].cnt; i++) {
             printf(" dist[%d] =  %d\n", j, dist[j].val[i]); 
         }
    } 
}
