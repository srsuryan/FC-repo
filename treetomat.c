#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "qlib.h"

int mat[10][10] = {0};

typedef  struct llist_ {
  int i;
  int p;
  void *parent;
  struct llist_ *prev;
  struct llist_ *next;
} llist_td;

typedef struct pack_ {
  int i;
  int p;
  void *ptr;
} pack_td;
 
node_td *root;
llist_td *start;

void
cons_bfs ()
{
   llist_td  *last, *sgl, *sglL, *sglR;
   node_td *parent, *tlft, *trgt, *node;
 
   start = (llist_td *) calloc(1, sizeof(llist_td));
   start->i = root->i;
   start->p = -1;
   start->parent = root;

   sgl = start;
   last = sgl;
 
   while (sgl) {
       node = sgl->parent;
       sglL = sglR = NULL;

       if (!node) {
	   printf("FATAL error sgl %d\n", sgl->i);
	   return;
       }

       if ( (!node->left &&
	   !node->right)) {
	   sgl = sgl->next;
	   continue;
       }	
       
       if (node->left) {
           sglL = (llist_td *) calloc(1, sizeof(llist_td));
	   tlft = node->left;
           sglL->i = tlft->i;
	   sglL->p = node->i;
	   sglL->parent = tlft;
	   last->next = sglL;
	   sglL->prev = last;
	   last = sglL;
       }

       if (node->right) {
           sglR = (llist_td *) calloc(1, sizeof(llist_td));
	   trgt = node->right;
           sglR->i = trgt->i;
	   sglR->p = node->i;
	   sglR->parent = trgt;
           last->next = sglR;
	   sglR->prev = last;
	   last = sglR;
	}

	sgl = sgl->next;
   }
}

void
set_mat (int i, int j)
{
   if (!((i >= 0) && (i <= 5))) return;

   if (!((j >= 0) && (j <= 5))) return;

   mat[i][j] = 1;
   printf(" mat[%d][%d] =%d\n", i, j, mat[i][j]);
}

llist_td *
get_sgl_parent (llist_td *sgl)
{

   int p = sgl->p;
   if (p == -1) return NULL;
  
  sgl = sgl->prev;
  while (sgl) {
	 if (sgl->p == p) return sgl;
	sgl = sgl->prev; 
  }
 
  return sgl;
}

qelem_td *
get_pack_parent (qelem_td *qelem)
{
   pack_td *pack = NULL;

   pack = (pack_td *)qelem->ptr;
   int p = pack->p;
   printf("%s p %d\n", __FUNCTION__, p);
   if (p == -1) return NULL;

  qelem = qelem->next;
  while (qelem) {
  	 pack = (pack_td *)qelem->ptr;
   	printf("%s_2() p %d\n", __FUNCTION__, pack->p);
         if (pack->i == p) return qelem;
  	 qelem = qelem->next;
  }

  return NULL;
}

int
main (int argc, char **argv)
{
	pack_td *pack;
	qelem_td *qelem = NULL;
	queue_td *q = NULL;
	int rv, i, j, *a, fd1, fd2;
	llist_td *sgl, *psgl;
	node_td *node, *node1, *node2, *parent, *save_node;

	if (argc == 1) {
	    printf("Enter parameters\n");
	    return 0;
	}

	root = tree_create_bft(argc, argv);
	inorder(root);
	rv = lib_init(QUEUE, &q, &fd2);
	if (!rv || !q) {
	    printf("Lib init failed %d %p\n", rv, q);
	    return 1;
	}
	pack = (pack_td *)calloc(1, sizeof(pack_td));
	pack->i = root->i;
        pack->p = -1;
	pack->ptr = root;
	qpush(fd2, (void *)pack);

	qelem = qhead(fd2);
	printf("Inorder done %p\n", qelem->ptr);
	while (qelem) {
	    pack = (pack_td *)qelem->ptr;
	    node = (node_td *)pack->ptr;
	    printf(" <<%d>> ", node->i);	
	    if (node->left) {
	        pack = (pack_td *)calloc(1, sizeof(pack_td));
	        pack->i = node->left->i;
                pack->p = node->i;
		pack->ptr = (void *)node->left;
	        qpush(fd2, (void *)pack);
	    }
            if (node->right) {
	        pack = (pack_td *)calloc(1, sizeof(pack_td));
	        pack->i = node->right->i;
                pack->p = node->i;
		pack->ptr = (void *)node->right;
	        qpush(fd2, (void *)pack);
	    }
	    qelem = qelem->prev;
       }     
       printf("POP NOW\n");

       qelem = qtail(fd2);
       while (qelem) {
	   pack = (pack_td *) qelem->ptr;
       	   printf(" POP<<%d p %d>> \n", pack->i, pack->p);	
	   qelem = qelem->prev;
       }
#if 1
	int c;
	qelem_td *p_q_elem;
	pack_td *p_pack;

        qelem = qhead(fd2);
	while (qelem) {
		pack = (pack_td *) qelem->ptr;
		printf(" p %d, i %d", pack->p, pack->i);
		getchar();
		set_mat(pack->p, pack->i);
		p_q_elem = get_pack_parent(qelem);
		c = pack->i;
		while (p_q_elem) {
			p_pack = (pack_td *) p_q_elem->ptr;
			//if (c == -1) {
			  //  c = p_pack->i;
			//}
			printf(" Set at %d %d ", p_pack->p, c);
			getchar();
			set_mat(p_pack->p, c);
			//set_mat(p, p_pack->i);
			p_q_elem = get_pack_parent(p_q_elem);
		}
		qelem = qelem->next;
	}

       for (i = 0; i < 6; i++) {
          for (j = 0; j < 6; j++) {
	      printf(" %d ", mat[i][j]); 
	  }
	  printf("\n");
       }
#endif	
}
