#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../ll/util.h"
#include "../ll/ll.h"
#include "../qlib.h"
#include "treelib.h"

#if 0
int
node_common (node_td *node, int *c, int v1, int v2, int *acc)
{
    int rv1, rv2, ov = *c;

    if (!node) return 0;
    
    rv1 = node_common(node->left, c, v1, v2, acc);

    if ((node->i == v1) || (node->i == v2)) {
            /* This has to be the second node */
            if (!(*c)) {
                *acc = 1;
            } else {
                *acc = 0;
            }
            (*c)++;
            printf("1st Node found %d count %d\n", node->i, *c);
            return 1;
   } 

    rv2 = node_common(node->right, c, v1, v2, acc);

    if ((ov != *c) && (*acc)) {
        (*c)++;
    }

    if (rv1 || rv2) {
        if (!acc) {
            (*c)++; 
        }
        printf("Inbetween Node found %d count %d\n", node->i, *c);
    }
    return (rv1 || rv2);
}
#endif

node_td *cmn = NULL;

int
node_common (node_td *node, int *c, int v1, int v2, int *acc)
{
    int rv, skip = 0, ov = *c;

    if (!node) return 0;
    
    rv = node_common(node->left, c, v1, v2, acc);
    if (rv) return rv;

    if (cmn) {
        if (cmn->left == node) {
            cmn = node;
        } else if(cmn->right == node) {
            cmn = node;
        } 
        
        return 1;
    }

    if ((node->i == v1) || (node->i == v2)) {
        if (!(*c)) {
            printf("Start of count %d\n", node->i);
        } else {
            cmn = node;
            printf("End of count %d\n", node->i);
        }
        (*c)++;
    }

    rv = node_common(node->right, c, v1, v2, acc);
    if (rv) return rv;
    
    return 0;
}

int
main (int argc, char *argv[])
{
    int *a, c = 0, acc = 0;
    node_td *root, *prev, *node, *ntof = NULL;

    a = get_from_main(argc, argv);
    root = cons_tree_ln(a);
    print_tr(root, "main m");
    acc = 0;
    c = 0;
    printf("Nodes 2 4 found %d distance %d cmn %d \n", node_common(root, &c, 2, 4, &acc), c, cmn->i);
    acc = 0;
    c = 0;
    cmn = NULL;
    printf("Nodes 2 5 found %d distance %d %d\n", node_common(root, &c, 2, 5, &acc), c, cmn ? cmn->i : -1);
    acc = 0;
    c = 0;
    cmn = NULL;
    printf("Nodes 4 8 found %d distance %d  %d \n", node_common(root, &c, 4, 8, &acc), c, cmn ? cmn->i : -1);
    getchar();
    acc = 0;
    c = 0;
    printf("Nodes 1 4 found %d distance %d %d \n", node_common(root, &c, 1, 4, &acc), c), cmn->i;
    acc = 0;
    c = 0;
    printf("Nodes 1 2 found %d distance %d %d\n", node_common(root, &c, 1, 2, &acc), c, cmn->i);
    acc = 0;
    c = 0;
    getchar();
    printf("Nodes 1 5 found %d distance %d \n", node_common(root, &c, 1, 5, &acc), c);
    acc = 0;
    c = 0;
    printf("Nodes 1 3 found %d distance %d \n", node_common(root, &c, 1, 3, &acc), c);
    acc = 0;
    c = 0;
    printf("Nodes 1 6 found %d distance %d \n", node_common(root, &c, 1, 6, &acc), c);
    acc = 0;
    c = 0;
    printf("Nodes 1 8 found %d distance %d \n", node_common(root, &c, 1, 8, &acc), c);
    acc = 0;
    c = 0;
    printf("Nodes 1 3 found %d distance %d \n", node_common(root, &c, 1, 3, &acc), c);
    acc = 0;
    c = 0;
    printf("Nodes 1 7 found %d distance %d \n", node_common(root, &c, 1, 7, &acc), c);
    acc = 0;
    c = 0;
    printf("Nodes 3 6 found %d distance %d \n", node_common(root, &c, 3, 6, &acc), c);
    acc = 0;
    c = 0;
    printf("Nodes 3 7 found %d distance %d \n", node_common(root, &c, 3, 7, &acc), c);
    getchar();
    printf("Nodes found %d distance %d \n", node_common(root, &c, 3, 2, &acc), c);
    printf("Nodes found %d distance %d \n", node_common(root, &c, 3, 4, &acc), c);
    printf("Nodes found %d distance %d \n", node_common(root, &c, 3, 5, &acc), c);
    printf("Nodes found %d distance %d \n", node_common(root, &c, 5, 6, &acc), c);
    printf("Nodes found %d distance %d \n", node_common(root, &c, 5, 6, &acc), c);
    printf("Nodes found %d distance %d \n", node_common(root, &c, 5, 7, &acc), c);
    printf("Nodes found %d distance %d \n", node_common(root, &c, 5, 3, &acc), c);
    printf("Nodes found %d distance %d \n", node_common(root, &c, 4, 6, &acc), c);
    printf("Nodes found %d distance %d \n", node_common(root, &c, 4, 8, &acc), c);
    printf("Nodes found %d distance %d \n", node_common(root, &c, 4, 3, &acc), c);
    printf("Nodes found %d distance %d \n", node_common(root, &c, 4, 7, &acc), c);
}
