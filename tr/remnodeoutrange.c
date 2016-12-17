#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../ll/util.h"
#include "../qlib.h"
#include "treelib.h"

static node_td *root = NULL;

#define MIN_RANGE -10
#define MAX_RANGE 13
int debug; 

node_td*
process_range (node_td *node, node_td *parent)
{
    int ss = 0;
    
    if (!node) return NULL;

    if (!root) {
        root = node;
    }

    if (node->i < MIN_RANGE) {
        /* 
         * Anything on the left is going to be of lower range, 
         * so dont bother 
         */
        node->left = NULL;
        if (parent->left == node) {
            parent->left = node->right;
        } else if (parent->right == node) {
            parent->right = node->right;
        }
        ss = TRUE;
    } else if (node->i > MAX_RANGE) {
        node->right = NULL;
        if (parent->left == node) {
            parent->left = node->left;
        } else if (parent->right == node) {
            parent->right = node->left;
        }
        ss = TRUE;
    }

    process_range(node->left, ss ? parent : node);
    process_range(node->right, ss ? parent : node);

    return root;
}

// A utility function to create a new BST node with i as given num
node_td* newNode(int num)
{
    node_td * temp = (node_td *)calloc(1, sizeof(node_td));
    temp->i = num;
    temp->left = temp->right = NULL;
    return temp;
}
// A utility function to insert a given i to BST
node_td* insert(node_td* root, int i)
{
    if (root == NULL)
       return newNode(i);
    if (root->i > i)
       root->left = insert(root->left, i);
    else
       root->right = insert(root->right, i);
    return root;
}
 
    int   
main (int argc, char *argv[])  
{       
    root = insert(root, 6);
    root = insert(root, -13);
    root = insert(root, 14);
    root = insert(root, -8);
    root = insert(root, 15);
    root = insert(root, 13);
    root = insert(root, 7);
 
   print_tr(root, "main"); 
   process_range(root, NULL);
   print_tr(root, "post-process");
}

