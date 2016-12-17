#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../qlib.h"
#include "../ll/util.h"
//#include "treelib.c"

/*  http://www.geeksforgeeks.org/find-distance-two-given-nodes/
 *  Find distance between two nodes, first find common parent between the two and then count the  dist
 */

int debug = 1;
typedef struct wnode_td_ {
    int set;
    int d;
    int visited;
    node_td *ptr;
} wnode_td;

static void
inorder (node_td *node)
{
    if (!node) return;

    inorder(node->left);
    printf(" In %d ", node->i);
    inorder(node->right);
}


void
insert_val (node_td *node, int i, node_td *prev)
{
    node_td *nn;

    if (!node) {
        if (i > prev->i) {
            if (prev->right != NULL) {
                printf("Something wrong\n");
                return;
            }
            nn = calloc(1, sizeof(node_td));
            nn->i = i;
            prev->right = nn;
            return;
        } else {
            if (prev->left != NULL) {
                printf("Something wrong\n");
                return;
            }
            nn = calloc(1, sizeof(node_td));
            nn->i = i;
            prev->left = nn;
            return;
        }
    }

    prev = node;
    if (node->i < i) {
        insert_val(node->right, i, prev);
    } else {
        insert_val(node->left, i, prev);
    }
}

node_td *
cons_tree (int a[])
{
    int i = 0;
    node_td *root;

    root = calloc(1, sizeof(node_td));
    root->i = a[i];
    i = 1;
    while (a[i] != INVALID) {
        insert_val(root, a[i], root);
        i++;
    }
    return root;
}


node_td *
mark_node (int fd, int *d)
{
    int count = 1;
    wnode_td *wnode;
    selem_td *selem;

    selem = shead(fd);
    if (!selem) {
        printf("Nothing in queue head, returning\n");
        return NULL;  
    }   

    while (selem) {
        wnode = (wnode_td *) selem->ptr;
        if  (wnode->set) {
             printf("Flag found on %d\n", wnode->ptr->i);
             *d = wnode->d + count;
             return (node_td *)wnode->ptr;
        } else {
            wnode->set = 1;
            wnode->d += count;
            printf("Flag set on %d\n", wnode->ptr->i);
        }
        selem = selem->next;
        count++;
    }

    return NULL;
}


node_td *
traverse (node_td *node, int fd, int rv1, int rv2, int *d)
{
    selem_td *selem;
    node_td *found = NULL;
    wnode_td *wnode;

    do {
        while (node) {


            wnode = calloc(1, sizeof(wnode_td));
            wnode->ptr = node;
            spush(fd, wnode);
            if ((node->i == rv1) || (node->i == rv2)) {
                found = mark_node(fd, d);      
                if (found) return found;      
            }
            if (debug) {
                printf("Pushed %d\n", node->i);
            }
            node = node->left;
        }
#if 1
        selem = shead(fd);
        wnode = selem->ptr;
        node = wnode->ptr;
        if (!node->right || wnode->visited) {
#endif
            wnode = (wnode_td *)spop(fd);
       } else {
            wnode->visited = 1;
       }

        if (!wnode) return NULL;

        node = wnode->ptr;

        if (debug) {
            printf("poped Node %d\n", node->i);
        }
        node = node->right;
    } while (1);
    return node;
}

int
main (int argc, char *argv[])
{
    node_td *root, *node;
    int rv, fd, a[32] = {10, 5, 4, 6, 30, 26, 37, 28, INVALID}, d = -1;
    stack_td *s1;

    rv = slib_init(STACK, &s1, &fd);
    if (!rv || !s1) {
        printf("Lib init failed %d %p\n", rv, s1);
        return 1;
    }

    root = cons_tree(a);
    inorder(root);
    
    node = traverse(root, fd, 4, 37, &d);
    printf("\nCommon node %d Dist %d\n", node ? node->i : -1, d);
}

