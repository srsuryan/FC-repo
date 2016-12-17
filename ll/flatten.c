// C program for flattening a linked list
#include <stdio.h>
#include <stdlib.h>
 
// A Linked List Node
typedef struct Node
{
    int data;
    struct Node *right;
    struct Node *down;
} Node;
 
 
/* Function to print nodes in the flattened linked list */
void printList(Node *node)
{
    while (node != NULL)
    {
        printf("%d ", node->data);
        node = node->down;
    }
}

void printListR(Node *node)
{
    while (node != NULL)
    {
        printf("%d ", node->data);
        node = node->right;
    }
}

/* A utility function to insert a new node at the begining
   of linked list */
void push (Node** head_ref, int new_data)
{
    /* allocate node */
    Node* new_node = (Node *) malloc(sizeof(Node));
    new_node->right = NULL;
 
    /* put in the data  */
    new_node->data  = new_data;
 
    /* link the old list off the new node */
    new_node->down = (*head_ref);
 
    /* move the head to point to the new node */
    (*head_ref)    = new_node;
}

Node *
merge_ll (Node *l1, Node *l2)
{
    Node *start = l1, *prev;

    if (!l1 || !l2) return NULL;

#if 0
    while (l1 && l1->data > l2->data) {
         if (!start) {
              start = l1;
              last = &l1->next;i
        } else {
              *last = l1; 
              last = &l1->next;
        }
        l1t = l1->next;
        l1->next = NULL;
        l1 = l1t;
    }
#endif
    prev = NULL;
    while (l1 && (l1->data < l2->data)) {
        prev = l1;
        l1 = l1->right;
    }

    if (prev) {
        prev->right = l2;
        l2->right = l1;
        return start;
    } 

    prev = NULL;
    start = l2;
    while (l2 && (l2->data > l1->data)) {
        prev = l2;
        l2 = l2->right;
    }
    
    if (prev) {
        prev->right = l1;
        l1->right = l2;
    }
    return start;
}

Node *
sort_ll (Node *node)
{
    Node *pp, *uns = NULL, **luns = NULL, *prev;

    if (!node) return NULL;

    prev = node;
    node = node->right;
    while (node) {
        if (prev->data > node->data) {
            if (!pp) {
                uns = pp;
                luns = &pp->right;
                pp->right = NULL;
                prev = node;
                node = node->right;
                continue;
            }
            pp->right = node;
            prev->right = NULL;
            if (!uns) {
                uns = prev;
            } else {
                *luns = prev;
            }
            luns = &prev->right;
            
        } else {
            pp = prev;
        }
        prev = node;
        node = node->right;
    }

    return uns;
}
        

    
// Driver program to test above functions
int main()
{
    Node* root = NULL;
 
    /* Let us create the following linked list
       5 -> 10 -> 19 -> 28
       |    |     |     |
       V    V     V     V
       7    20    22    35
       |          |     |
       V          V     V
       8          50    40
       |                |
       V                V
       30               45
    */
    push( &root, 30 );
    push( &root, 8 );
    push( &root, 7 );
    push( &root, 5 );
 
    push( &( root->right ), 20 );
    push( &( root->right ), 10 );
 
    push( &( root->right->right ), 50 );
    push( &( root->right->right ), 22 );
    push( &( root->right->right ), 19 );
 
    push( &( root->right->right->right ), 45 );
    push( &( root->right->right->right ), 40 );
    push( &( root->right->right->right ), 35 );
    push( &( root->right->right->right ), 28 );
 
    // Let us flatten the list
//    root = flatten(root);
 
    // Let us print the flatened linked list
    Node *node, *next, *prev, *print;

    next = root;
    do {
        node = next;
        next = node->right;
        node->right = NULL;
        print = node;
        while (node) {
            prev = node;
            node = node->down;
            prev->right = node;
        }

        prev->right = next;
        printListR(print);
        printf("\n %p\n", next); 
       // getchar();
    } while (next);
  
    //printListR(root);

    printf("==========\n");
    node = sort_ll(root); 
    printListR(node);
    printf("==========\n");
    printListR(root);
    printf("\n");
    while (node) {
        next = node->right;
        root = merge_ll(root, node);
        printListR(root);
        getchar();
        node = next;
    }
    return 0;
}
