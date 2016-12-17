#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 *              1
 *          2          3
 *      4      5   6      7
 * => 1 2 3 4 5 6 7 
 * struct has additional fied caleld nextRight in each node. So join 2->3, 4->5->6->7
 */


typedef  struct node_ {
  int i;
  struct node_ *left;
  struct node_ *right;
  struct node_ *nextRight;
} node_td;

node_td *root;
void
tree_create (node_td *node, int i)
{

    node_td *trav, *prevl, *prevr;

    trav = root;

    while (trav) {
        if (i > trav->i) {
            prevr = trav;
            prevl = NULL;
            trav = trav->right;
        } else if ( i < trav->i) {
            prevr = NULL;
            prevl = trav;
            trav = trav->left;
        } else {
            printf("Value not added %d exists\n", i);
            return;
        }
    }

    if (prevl) {
        prevl->left = node;
    } else if (prevr) {
        prevr->right = node;
    }
}



void
inorder (node_td *node) 
{
    node_td *save_node, *cnode, **next;

    if (!node) return;

#if 1
    cnode = node->left ? node->left : node->right;
    next = &(cnode->nextRight);
    save_node = node;

    while (node && cnode) {
        *next = (cnode == node->left) ? node->right : NULL;
        if (*next) {
            next = &(*next)->nextRight;
        }

        node = node->nextRight;
        if (node) {
            cnode = node->left ? node->left : node->right;
            *next = cnode;
            if (*next) {
                next = &(*next)->nextRight;
            }
        }
    }
    node = save_node;
#endif
    inorder(node->left);
    printf(" <<%d>> ", node->i);
    inorder(node->right);
}

node_td *
search_node (int i, node_td *n) 
{
    node_td *r;

    if (!n) return NULL;
    
    if (n->i == i) return n;
    
    r = search_node(i, n->left);
    if (r) return r;
    r = search_node(i, n->right);
    if (r) return r;
 
    return NULL;
}
    
int
main (int argc, char **argv)
{
    int i;
    node_td *node, *save_node;
    
    if (argc == 1) {
        printf("Enter parameters\n");
        return 0;
    }

    root = (node_td *)calloc(1, sizeof(node_td));
    root->i = (int)strtol(argv[1], 0, 0);

    for (i =  1 ; i < argc - 1; i++) {
        node = (node_td *)calloc(1, sizeof(node_td));
        node->i = (int)strtol(argv[i+1], 0, 0);
        tree_create(node, node->i);
    }
    inorder(root);
    printf("\n");
   
    getchar(); 
    node = root;
    while (node) {
        printf(" [T %d  ] ", node->i);
        save_node = node;
        node = node->nextRight;
        while (node) {
            printf(" [C %d  ] ", node->i);
            node = node->nextRight;
        }
        printf("\n");
        node = save_node;
        node = node->left;
    }
    node = search_node(75, root);
    while (node) {
        while (node) {
            printf(" [C %d  ] ", node->i);
            node = node->nextRight;
        }
    }
    printf("\n");
}
