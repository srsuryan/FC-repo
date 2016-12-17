
#include <stdio.h>
#include <stdlib.h>

/*
 * Given a Binary Tree, find size of the Largest Independent Set(LIS) in it. 
 * A subset of all tree nodes is an independent set if there is no edge between any two nodes of the subset.
 * For example, consider the following binary tree. 
 * The largest independent set(LIS) is {10, 40, 60, 70, 80} and size of the LIS is 5.
 */

typedef enum status_flag_ {
    DCF = 0,
    IDC,
} flags_td;

typedef struct node_td_ {
    int data;
    struct node_td_ *left; 
    struct node_td_ *right;
} node_td;

flags_td
inorder (node_td *node, int *cnt)
{
    int cll = 0, clr = 0;
    flags_td fld, flr;

    if (!node) return DCF;

    fld = inorder(node->left, &cll);
    
    flr = inorder(node->right, &clr);

    if (!cll && !clr) {
        /* leaf node */
        *cnt = 1;
        return DCF;
    } 
    
    if (fld == flr) {
        if (fld == DCF) {
            *cnt = cll+clr;
            return IDC;
        }
        /* Both are indirect connection */
        *cnt = cll+clr+1;
        return DCF;
    } else {
        *cnt = cll+clr;
        return IDC;
    }
}

// A utility function to create a node
node_td* newNode( int data )
{
    node_td *temp = (node_td *) malloc( sizeof(node_td) );
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}
 
// Driver program to test above functions
int main()
{
    int count = 0;
    // Let us construct the tree given in the above diagram
    node_td *root         = newNode(20);
    root->left                = newNode(8);
    root->left->left          = newNode(4);
    root->left->right         = newNode(12);
    root->left->right->left   = newNode(10);
    root->left->right->right  = newNode(14);
    root->right               = newNode(22);
    root->right->right        = newNode(25);

    inorder(root, &count); 
    printf ("Size of the Largest Independent Set is %d ", count);
 
    return 0;
}
