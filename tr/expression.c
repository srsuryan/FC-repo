#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * INCOMP
 * http://www.geeksforgeeks.org/evaluation-of-expression-tree/
 * +*5-4 => +20-100-20
 */

int debug = 0;
typedef struct node_td_ {
    int i;
    struct node_td_ *left;
    struct node_td_ *right;
}node_td;

node_td *root;

typedef enum dir_td_ {
    MODIFY = 0,
    NONE,
} dir_td;

char
check_for_num (int i)
{
    switch (i) {
    case '+' :
        return '+';
    case '*':
        return '*';
    case '-':
        return '-';
    case '/':
        return '/';
    default:
        return (char)-1;
    }
}

    
void
inorder (node_td *node)
{
    char rv;

    if (!node) return;
    
    inorder(node->left);
    rv = check_for_num(node->i);
    if (rv != -1) {
        printf(" %c ", rv);
    } else {
        printf(" %d ", node->i);
    }
     
    inorder(node->right);
}

int
get_val (int *a, int nv)
{

    switch (a[1]) {
    case '+' :
        return a[0] + nv ;
    case '*':
        return a[0] * nv;
    case '-':
        return a[0] - nv;
    case '/':
        return a[0] / nv;
    default:
        printf("Wrong value \n");
        return (char)-1;
    }
}

dir_td
traverse (node_td *node, int *a, int *c, int *nv)
{
    node_td *nn;
    int rv;
    dir_td dir;

    if (!node) return NONE;

    if (*c == 2) {
        /* check if this is a number */
        rv = check_for_num(node->i);
        if (rv == -1) {
            /* Its a number, it has to be a leaf */
            (*c)++;
            *nv = get_val(a, node->i);
            if (debug) 
                printf("1. %d %c val %d %d\n", a[0], a[1], *nv, node->i);
            *c = 0;
            memset(a, 0, sizeof(int)*3);
            return MODIFY;
        } 
        *c = 0;
        memset(a, 0, sizeof(int)*3);
    }

    dir = traverse(node->left, a, c, nv);

    if (dir == MODIFY) {
        nn = calloc(1, sizeof(node_td));
        nn->i = *nv;
        node->left = nn;
        memset(a, 0, sizeof(int)*3);
        if (debug)
            inorder(root);
        a[0] = *nv;
        *c = 1;
    }

    a[(*c)] = node->i;  
    (*c)++;
    
    dir = traverse(node->right, a, c, nv);
    
    if (dir == MODIFY) {
        node->i = *nv;
        node->left = node->right = NULL;
        if (debug)
            inorder(root);
        memset(a, 0, sizeof(int)*3);
        a[0] = *nv;
        *c = 1;
    }
    
    return NONE;
}

node_td *
newnode (int i)
{
   node_td *node;
 
   node = calloc(1, sizeof(node_td));
   node->i = i;
   return node;
}
    
 
//driver function to check the above program
int main()
{
    int a[3] = {0};
    int c = 0, nv = 0;
    // create a syntax tree
#if 1
    root = newnode('+');
    root->left = newnode('*');
    root->left->left = newnode(5);
    root->left->right = newnode(4);
    root->right = newnode('-');
    root->right->left = newnode(100);
    root->right->right = newnode(20);
 
    while (root->left || root->right) {
        traverse(root, a, &c, &nv);
        memset(a, 0, sizeof(int)*3);
        c = nv = 0;
    }
    inorder(root);
    printf("\n");
#endif
    root = newnode('+');
    root->left = newnode('*');
    root->left->left = newnode(5);
    root->left->right = newnode(4);
    root->right = newnode('-');
    root->right->left = newnode(100);
    root->right->right = newnode('/');
    root->right->right->left = newnode(20);
    root->right->right->right = newnode(2);
 
    printf("\n");
    while (root->left || root->right) {
        traverse(root, a, &c, &nv);
        memset(a, 0, sizeof(int)*3);
        c = nv = 0;
    }
    inorder(root);
    printf("\n");
    return 0;
}
