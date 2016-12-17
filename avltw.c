#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Write a function to count number of smaller elements on right of each element in an array. Given an unsorted array arr[] of distinct integers, construct another array countSmaller[] such that countSmaller[i] contains count of smaller elements on right side of each element arr[i] in array.

Examples:

Input:   arr[] =  {12, 1, 2, 3, 0, 11, 4}
Output:  countSmaller[]  =  {6, 1, 1, 1, 0, 1, 0} 

(Corner Cases)
Input:   arr[] =  {5, 4, 3, 2, 1}
Output:  countSmaller[]  =  {4, 3, 2, 1, 0} 

Input:   arr[] =  {1, 2, 3, 4, 5}
Output:  countSmaller[]  =  {0, 0, 0, 0, 0}

http://www.geeksforgeeks.org/count-smaller-elements-on-right-side/
Solution is unique 

Build a avl tree from right of array to left. As we build, store of sub array. While traversing for new element, if the element is greater than one of the nodes, find the size of left of that node + 1.
*/


typedef struct avl_node_ {
     int i;
     int ht;
     int size;
     struct avl_node_ *left;
     struct avl_node_ *right;
} avl_node;

int debug = 1;
void
avl_do_ll_lr (avl_node **gp, avl_node **p, avl_node **nn);
avl_node *
avl_do_ll_ll (avl_node **gp, avl_node **p, avl_node **nn);
avl_node *
avl_do_rr_check (avl_node *gp, avl_node *p, avl_node *nn);
avl_node*
avl_do_ll_check (avl_node *gp, avl_node *p, avl_node *nn);

avl_node *
avl_do_rr_rr (avl_node **gp, avl_node **p, avl_node **nn);
void
avl_do_rr_rl (avl_node **gp, avl_node **p, avl_node **nn);

int get_ht_right (avl_node *p);
int get_ht_left (avl_node *p);


avl_node *root = NULL;

void
inorder (avl_node *node)
{
   if (!node) return;
 
   inorder(node->left);
   printf(" <%d ht %d %s s %d> ", node->i, node->ht,
	 root == node ? "r" : "", node->size);
   inorder(node->right);
}

int
avl_create (avl_node *node, int c, int *count)
{
   int right, left, htr, htl, balance;
   avl_node *p = NULL, *gp = NULL, *gp2, *newnode, *nn;

   if (!node) return -1;

   while (node) {
	
	if (!p) {
	    p = node;
	    gp = NULL;
	    gp2 = NULL;
	} else {
	    gp2 = gp;
	    gp = p;
	    p = node;
	}
        
	if (c > node->i) {
	    node->size++;
	    *count = *count + (node->left ? node->left->size : 0) + 1;
            printf("\nNode %d size %d count %d\n", node->i, node->size, *count);
	    //getchar();
	    node = node->right;	
	} else if (c < node->i) {
	    node->size++;
	    node = node->left;
	} else {
	    return -1;
	}
    }

    if (c > p->i) {
	p->right = calloc(1, sizeof(avl_node));
	newnode = p->right;
	newnode->i = c;
	newnode->ht = p->ht+1;
	newnode->size = 1;
	right = 1;
	left = !right;
    } else {
	p->left = calloc(1, sizeof(avl_node));
	newnode = p->left;
	newnode->i = c;
	newnode->ht = p->ht+1;
	newnode->size = 1;
	left = 1;
	right = !left;
    }
	
    if (!gp) {
        if (!root) root = newnode;
        return 0; 	
    } else {
	if (newnode->i > gp->i) {
	    /* added to right */
	    htl = get_ht_left(gp);
	    htr = newnode->ht;
	} else {
	   htr = get_ht_right(gp);
	   htl = newnode->ht;
	}
    }
	
    balance = htl - htr;

    if (debug) {
    	printf("[%d p %d gp %d] balance %d <%d %d> ", newnode->i, p->i, gp->i, 
		balance, htl, htr);
	//getchar();
    }
    switch (balance) {
    case -2:
       /* RR case */
       
       nn = avl_do_rr_check(gp, p, newnode);
       if (gp2) {
	   gp2->right = nn;
       }
       break;
    case -1:
    case 0:
    case 1:
      break;
    case 2:
	nn = avl_do_ll_check(gp, p, newnode);
	if (gp2) {
	    printf("YELL nn %d gp2 %d LEFT %p RIGHT %p\n", nn->i, gp2->i, gp2->right, gp2->left);
	    if (gp2->i < nn->i) 
	        gp2->right = nn;
	    else
		gp2->left = nn;
	}
        
      break;
    default:
	return -1;
    }
	
    return 0;
}	    
	 
int
get_ht_right (avl_node *p)
{
   if (!p->right) return p->ht;
  
   return p->right->ht;
}

int
get_ht_left (avl_node *p)
{
   if (!p->left) return p->ht;
  
   return p->left->ht;
}
 
avl_node *
avl_do_ll_check (avl_node *gp, avl_node *p, avl_node *nn)
{
    avl_node *node = NULL;

    if (p->right) {
        /* RL case first*/
        avl_do_ll_lr(&gp, &p, &nn);
    }

    node = avl_do_ll_ll(&gp, &p, &nn);
    return node;
}
 
void
avl_do_ll_lr (avl_node **gp, avl_node **p, avl_node **nn)
{
	avl_node *c;

        (*gp)->left = *nn;
        c = (*nn)->left;
        (*nn)->left = *p;
        (*p)->right  = c;

        c = *nn;
        *nn = *p;
        *p = c;
}

int
get_size (avl_node *node)
{
   int lsz, rsz;

   if (node->left) {
	lsz = node->left->size;
   } else {
	lsz = 0;
   }

   if (node->right) {
       rsz = node->right->size;
   } else {
	rsz = 0;
   }
  
   return (lsz + rsz + 1);
}

avl_node *
avl_do_ll_ll (avl_node **gp, avl_node **p, avl_node **nn)
{

    avl_node *c, *save = *gp;
    
     c = (*p)->right;

    (*p)->right = *gp;
    (*gp)->left = c;

    c = *gp;
    *gp = *p;
    *p = c;

    (*gp)->ht--;
    (*p)->ht++;
    (*nn)->ht--;
 
    if (root == save) {
        root = *gp;
	printf("Old root %d new root %d\n", save->i, root->i);	
    }

    (*p)->size = get_size(*p);
    (*nn)->size = get_size(*nn);
    (*gp)->size = get_size(*gp);

    return *gp;
}
 
avl_node *
avl_do_rr_check (avl_node *gp, avl_node *p, avl_node *nn)
{
    avl_node *node = NULL;

    if (p->left) {
        /* RL case first*/
          avl_do_rr_rl(&gp, &p, &nn);
    }
 
    printf("rr check\n"); 
    //inorder(root);
    //getchar();
    node = avl_do_rr_rr(&gp, &p, &nn);
    return node;
}
 

void
avl_do_rr_rl (avl_node **gp, avl_node **p, avl_node **nn)
{
	avl_node *c;
	
	(*gp)->right = *nn;
	c = (*nn)->right;
	(*nn)->right = *p;
	(*p)->left  = c;

	c = *nn;
        *nn = *p;
	*p = c;
	(*p)->ht--;
	(*nn)->ht++;
    
	(*p)->size = get_size(*p);
    	(*nn)->size = get_size(*nn);
    	(*gp)->size = get_size(*gp);
}


avl_node *
avl_do_rr_rr (avl_node **gp, avl_node **p, avl_node **nn)
{
    avl_node *b, *save = *gp;
  
    b = (*p)->left;
   
    (*p)->left = *gp;
    (*gp)->right = b; 
 
    b = *gp;
    *gp = *p;
    *p = b;
 
    (*gp)->ht--;
    (*p)->ht++;
    (*nn)->ht--;
  
    if (root == save) {
        root = *gp;
	printf("Old root %d new root %d\n", save->i, root->i);	
    }
	(*p)->size = get_size(*p);
    	(*nn)->size = get_size(*nn);
    	(*gp)->size = get_size(*gp);
    return *gp;
}

int
main (int argc, char *argv[])
{
  int i = 0, j;// a[5] = {5, 4, 3, 2, 1};
  //int a[5] = {1, 2, 3, 4, 5};
  //int a[5] = {10, 20, 15, 25, 30};
  int a[7] = {10, 6, 15, 20, 30, 5, 7};
  int count[7] = {0}; 
 
  root = calloc(1, sizeof(avl_node));
  root->ht = 1;
  root->size = 1;
  root->i = a[6];
  
  //j = sizeof(a)/sizeof(int) ;
  j = 5, i = 5;
  while (j >= 0) {
      avl_create(root, a[j], &count[j]);
      inorder(root);
      getchar();
      j--;
      i--;
  }
     printf("\n==============================\n");
     printf("\n==============================\n");
  i = 0;
  while (i < sizeof(a)/sizeof(int)) {
      printf("Count %d ", count[i]);
      i++;
  }   
}
 
