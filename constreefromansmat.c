#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

int debug = 1;
int mat[6][6] = {
                 {0, 0, 0, 0, 0, 0},
                 {1, 0, 0, 0, 1, 0},
                 {0, 0, 0, 1, 0, 0},
                 {0, 0, 0, 0, 0, 0},
                 {0, 0, 0, 0, 0, 0},
                 {1, 1, 1, 1, 1, 0},
                };
typedef struct node_td_ {
    int i;
    struct node_td_ *left;
    struct node_td_ *right;
} node_td;

node_td hash[32] = {0};

typedef enum oper_ {
    ASGND = 0,
    EXISTS,
    INVALID,
} oper_td;

int is_mat_set (int i, int j)
{
    return mat[i][j];
}

void
fill_node_element (node_td *rn, int *a, int *i)
{
    if (!rn) return;

    fill_node_element(rn->left, a, i);
    a[*i] = rn->i;
    (*i)++;

    fill_node_element(rn->right, a, i);
}

void
inorder (node_td *rn)
{
  if (!rn) return;

  inorder(rn->left);
  printf(" node %d\n", rn->i);
  inorder(rn->right);
}

int
search_val (node_td *rn, int j)
{
    int res;

    if (!rn) return FALSE;

    res = search_val(rn->left, j);

    if (res == TRUE) return res;

    if (rn->i == j) return TRUE;

    res = search_val(rn->right, j);

    if (res == TRUE) return res;

    return FALSE;
}

oper_td
assign_link (int i, int j)
{
    node_td *ln, *rn, *nn;
    int a[32], pos = 0, res, k;

    for (k = 0; k < 32; k++) {
         a[k] = 0xFF;
    }

    if (!hash[i].left && !hash[i].right) {
        hash[i].left = &hash[j];
        if (debug) {
            printf("[3] (%d %d) %d->%d \n", i, j, hash[i].i, hash[j].i);
            getchar();
        }
        return ASGND;
    }

    rn = hash[i].right;

    if (rn) {
        res = search_val(rn, j);
        if (res) {
            if (debug) {
                printf("[1] %d-> Value %d exists\n", i, j);
                getchar();
            }
            return EXISTS;
        }
    }

    ln = hash[i].left;
    if (ln) {
        res = search_val(rn, j);
        if (res) {
            if (debug) {
                printf("[2] %d-> Value %d exists\n", i, j);
                getchar();
            }
            return EXISTS;
        }
    }

    if (ln && rn) {
        printf(" %d -> Addition of %d failed\n", i, j);
        return INVALID;
    }

    fill_node_element(ln ? ln : rn, a, &pos);
    k = 0;
    while (a[k] != 0xFF) {
        res = search_val(&hash[j], a[k]);
        if (debug) {
            printf("%d -> %d a[%d] = %d %s", i, j, k, a[k], res ? "Exists" : "Does not exists");
            getchar();
        }
        if (res) break;
        k++;
    }
    if (res) {
        if (ln) {
            hash[i].left = NULL;
            printf(" %d -> %d removed %d from left ", i, j, j);
        } else {
            hash[i].right = NULL;
            printf(" %d -> %d removed %d from right ", i, j, j);
        }
    }

            getchar();
    nn = &hash[j];
    if (ln) {
        hash[i].right = nn;
        printf(" %d -> %d Added %d on right \n", i, j, j);
    } else {
        hash[i].left = nn;
        printf(" %d -> %d Added %d on left \n", i, j, j);
    }
            getchar();
    return ASGND;
}

int
main (int argc, char *argv[])
{

    int i, j;

    for (i = 0; i < 32; i++) {
        hash[i].i = i;
    }

    for (i = 0; i < 6; i++) {
        for (j = 0; j < 6; j++) {
            if (mat[i][j]) {
                assign_link(i, j);
            }                
        }
    }
    for (i = 0; i < 6; i++) {
         printf("a[%d] = %d Left %d right %d\n", i, hash[i].i, hash[i].left ? hash[i].left->i : -1
                 , hash[i].right ? hash[i].right->i : -1);
    }
    inorder(&hash[5]);
}

