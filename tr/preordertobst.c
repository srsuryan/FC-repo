#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../ll/util.h"
#include "../ll/ll.h"
#include "../qlib.h"
#include "treelib.h"

/* given 1 arrays, find if these two arrays will form same bst or not */

int debug = 0;
void
find_range (int i, int *minl, int *maxr, int match, int *a)
{
    *minl = *maxr = -1;

    while (i >= 0) {
        if (match < a[i]) {
            if (*maxr == -1) {
                *maxr = i;
            } else if (*maxr > a[i]) {
                *maxr = a[i];
            }
        } else {
            if (*minl == -1) {
                *minl = a[i];
            } else if (*minl < a[i]) {
                *minl = i;
            }
        }
        i--;
    }
}

void
insert_node (node_td *node, node_td *toins)
{
    if (debug) {
        printf("Node to be inserted %d lookup at %d\n", toins ? toins->i : -1,
                node ? node->i : -1);
    }
    if ((!node) || (!toins)) {
        return;
    }

    if (node->i > toins->i) {
        if (node->left == NULL) {
            node->left = toins;
            return;
        }
        insert_node(node->left, toins);
    }

    if (node->i < toins->i) {
        if (node->right == NULL) {
            node->right = toins;
            return;
        }
        insert_node(node->right, toins);
    }
}

int   
main (int argc, char *argv[])  
{      
    node_td *b[32] = {0}; 
    int *a, i, minr, maxr, skip;
    node_td *root, *node;

   a = get_from_main(argc, argv);
  
   root = calloc(1, sizeof(node_td));
   b[0] = root;
   root->i = a[0];
   i = 1;
   while (a[i] != INVALID) {
       skip = 1;
       node = calloc(1, sizeof(node_td));
       node->i = a[i];
       b[i] = node; 
       find_range(i-1, &minr, &maxr, a[i], a);

       if (debug) {
           printf("Range for %d is %d %d \n", a[i], 
                   (minr != -1) ? a[minr] : -1,  (maxr != -1) ? a[maxr] : -1);
       }

       if (minr != -1) {
           node = b[minr];
           if (debug) {
                printf(" node %d %p %p\n", node->i, node->left, node->right);
           }
           if (node->i < a[i]) {
                if (node->right == NULL) {
                    node->right = b[i];
                    skip = 0;
                }
            } 
        }
       
        if ((skip) && (maxr != -1)) {
            node = b[maxr];
            if (debug) {
                printf(" node %d %p %p\n", node->i, node->left, node->right);
            }
            if (node->i > a[i]) {
                if (node->left == NULL) {
                    node->left = b[i];
                    skip = 0;
                }
            }
        }

        if (skip) {
            if (debug) {
                printf("Skipped for node %d. This should be due to new addition, insert into tree\n",
                    b[i]->i);
                getchar();
            }
            insert_node(node, b[i]);
        }
       i++; 
    }

    inorder(root);
    printf("\n");
}   

