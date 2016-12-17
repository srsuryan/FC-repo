#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../ll/util.h"
#include "../ll/ll.h"
#include "treelib.h"

int range[2] = {1, 45};

int 
withinrange (int i)
{
    if ((i >= range[0]) &&
        (i <= range[1])) {
        return 1;
    }
    return 0;
}

int
fallinr (node_td *node, int *count)
{
    int rv, rv2;

    if (!node) return 1;

    rv = fallinr(node->left, count);

    rv2 = fallinr(node->right, count);

    if (rv2*rv) {
        if (withinrange(node->i)) {
            if (debug) {
                printf("Node %d %d %d %d\n", node->i, rv2, rv, rv2*rv);
            }
            *count += 1;
            return 1;
        }
    }
    return 0;
}

 
// Utility function to create new node
node_td *newNode(int i)
{
    node_td *temp = calloc(1, sizeof(node_td));
    temp->i  = i;
    temp->left  = temp->right = NULL;
    return (temp);
}
 
    int
main (int argc, char *argv[])
{
    int *a, count = 0;
    node_td *root, *temp;
    
    root        = newNode(10);
    root->left        = newNode(5);
    root->right       = newNode(50);
    root->left->left  = newNode(1);
    root->right->left = newNode(40);
    root->right->right = newNode(100);
    debug = 1;
   // a = get_from_main(argc, argv);
   // root = cons_tree(a);
   // print_tr(root, "main");
    printf("Max nodes in range %d %d\n", fallinr(root, &count), count);
}

