#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __HAL_MFWD_EDM_H__
#define __HAL_MFWD_EDM_H__

typedef struct qelem_td_ {
   void *ptr;
   struct qelem_td_ *next;
   struct qelem_td_ *prev;
} qelem_td;

typedef struct queue_td_ {
   int total;
   qelem_td *head;
   qelem_td *tail;
} queue_td;

typedef struct selem_td_ {
   void *ptr;
   struct selem_td_ *next;
} selem_td;

typedef struct stack_td_ {
   int total;
   selem_td *head;
} stack_td;

typedef  struct node_ {
  int i;
  struct node_ *left;
  struct node_ *right;
} node_td;

void qpush(int fd, void *);

void* qpop (int fd);

qelem_td *qhead(int fd);
qelem_td *qtail(int fd);

typedef enum ds_type_ {
   STACK = 1,
   QUEUE,
} ds_type;

#define LMAX 32

node_td *
tree_create_bft (int argc, char *argv[]);
int qlib_init (ds_type type, queue_td **, int *fd);
int slib_init (ds_type type, stack_td **, int *fd);
int *get_from_main (int, char **);
void lib_done(int fd);
void spush (int fd, void *ptr);
void* spop(int fd);
selem_td *shead(int fd);
int stack_size (int fd);
int largestrect (int *a, int col);
queue_td * ts(int start, int mat[][4], int mr, int mc);

int find_min (int *a, int max);
int find_max (int *a, int max);

#endif
