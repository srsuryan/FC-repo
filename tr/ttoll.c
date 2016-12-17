#include <stdio.h>
#include <stdlib.h>
 
typedef struct Node_
{
    int data;
    struct Node_ *left, *right;
} Node;
 
Node* newNode(int data)
{
    Node* node = (Node *)calloc(1, sizeof(Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}
 
// Utility function for printing double linked list.
void printList(Node* head)
{
    Node *prev;

    printf("Extracted Double Linked list is:\n");
    while (head)
    {
        printf("%d ", head->data);
        prev = head;
        head = head->right;
    }
    
    printf("\n");
    while (prev) {
        printf("%d ", prev->data);
        prev = prev->left;
    }
}

void
inorder(Node *node)
{
    if (!node) return;

    inorder(node->left);
    printf(" %d ", node->data);
    inorder(node->right);
}

Node *prev = NULL, **last = NULL, *start;
void
ttoll (Node *node)
{
    if (!node) return;

    ttoll(node->left);
    
    if (!prev) {
        start = node;
    } else {
        node->left = prev;
        *last = node;
    }
    prev = node;
    last = &node->right;
    
    ttoll(node->right);
}


#if 0
void
ttoll (Node *nodei, Node **L, Node **R) 
{
    Node **lptr, *Lnode = NULL, *Rnode = NULL;

    if (!node) {
         *L = *R = NULL;
    }

    ttoll(node->left, &Llnode, &Lrnode);
    ttol(node->right, &Rlnode, &Rrnode);
    if (!Llnode && !Lrnode) {
        if (!Rlnode && !Rrnode) {
            /* This is a leaf node */
            *L = &node->left;
            *R = &node->right;
        } else {
            /* Left has no sub tree */
            *Rlnode = node;
        }
        *L = node->right;
        *R = Rrnode;
    } else if (Llnode && Lrnode) {
        node->left = Lrnode;
         
    }

}
#endif

// Driver program to test above function
int main()
{
    /* Constructing below tree
               5
             /   \
            3     6
           / \     \
          1   4     8
         / \       / \
        0   2     7   9  */
    Node* root = newNode(5);
    root->left = newNode(3);
    root->right = newNode(6);
    root->left->left = newNode(1);
    root->left->right = newNode(4);
    root->right->right = newNode(8);
    root->left->left->left = newNode(0);
    //root->left->left->right = newNode(2);
    //root->right->right->left = newNode(7);
    root->right->right->right = newNode(9);
 
    Node* head = NULL;
    
    inorder(root);
    printf("\n");
    ttoll(root);
    printList(start);
     
    return 0;
}
