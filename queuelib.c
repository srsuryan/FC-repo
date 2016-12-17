#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qlib.h"

queue_td queue[LMAX] = {0};

static int fd[LMAX] = {0};
static int libinit[LMAX]  = {0};

#define massert(ft, lineno, q)                         \
  if (!ft) {                                           \
      printf(" assert failed at Line %d\n ", lineno);  \
  }	

static int
search ()
{
  int i = 0;

  while (i < 32) {
      if (fd[i] == -1) {
	  fd[i] = i;
          return i;
      }
      i++;
  }
  return -1;
}

int
lib_init (ds_type type, queue_td **q, int *fdp)
{
   int rv = 0, i, fds;
   static ss_init = 1;
 
   if (ss_init) {
       for (i = 0; i < 32; i++) {
	    fd[i] = -1;
       }
       ss_init = 0;
   }   

   switch (type) {
   case QUEUE:
   case STACK:
       fds = search();
       if (fds == -1) {
	   printf(" fd is null");
	   return 1;
       }
       if (!libinit[fds]) {
	   libinit[fds] |= (type == STACK) ? STACK : QUEUE;
	   if (q) {
	       *q = &queue[fds];
	   }
	   *fdp = fds;
           rv = 1;	
	   printf("libinit %d q %p %p rv %d Q %d\n", libinit[fds], q, &queue[fds], rv, QUEUE);
       } else {
	   rv = 0;
       }
       break; 
   default:
      break;
   }
  return rv; 
}

void
lib_done (int fd)
{
	if (!libinit[fd]) return;
	
	 libinit[fd] = 0;
	 memset(&queue[fd], 0, sizeof(queue_td));
}

static int
verify_lib (int fd, ds_type type) 
{

   if (libinit[fd] == (STACK|QUEUE)) {
       massert(0, __LINE__, 0);
       return 0;
   }

   switch (type) {
   case STACK:
   case QUEUE:
       if (libinit[fd] & type) {
	 return 1;
       }
   default:
     break;
   }
   return 0;
}


void
qpush (int fd, void *ptr)
{
    qelem_td *qelem, *old_elem;

    if (!ptr) return;
    if (fd < 0 || fd >= 32) {
        massert(0, __LINE__, fd);
        return;
    }

    if (!verify_lib(fd, QUEUE)) {
        massert(0, __LINE__, 0);
        return; 	
    }

    qelem = (qelem_td *)calloc(1, sizeof(qelem_td));
    qelem->ptr = ptr;
    old_elem = queue[fd].head;
    queue[fd].head = qelem;
    qelem->next = old_elem;
    if (old_elem) {
        old_elem->prev = qelem;
    }
    queue[fd].total++;

    if (queue[fd].total == 1) {	
        queue[fd].tail = qelem;
    } else {
    }
    return; 	
}

qelem_td *
qhead (int fd)
{
    //qelem_td *qelem;
    //void *ptr;

    return queue[fd].head;
    //qelem = queue[fd].head;
    //if (qelem) return qelem->ptr;
    //return NULL;
}

qelem_td *
qtail (int fd)
{
   return queue[fd].tail;
}

void *
qpop (int fd)
{
   void *ptr;
   qelem_td *qelem, *old_elem, *prev;

   if (!verify_lib(fd, QUEUE)) {
       massert(0, __LINE__, 1);
       return NULL;
   }

   if (!queue[fd].total) {
       massert(queue[fd].tail == queue[fd].head, __LINE__, 1);	
       massert(queue[fd].tail == NULL, __LINE__, 1);	
       return NULL;
   }

   if (!queue[fd].head) {
       massert(queue[fd].tail == NULL, __LINE__, 1);	
       return NULL;
   }

   if (!queue[fd].tail) {
       printf("Fatal error queue head %p queue[fd].tail is NULL\n", queue[fd].head);
       return NULL;	
   }

   if (queue[fd].total == 1) {
       massert(queue[fd].head == queue[fd].tail, __LINE__, 1);
       queue[fd].total--;
       qelem = queue[fd].head;
       queue[fd].head = queue[fd].tail = NULL;
       ptr = qelem->ptr;
       free(qelem);
       return ptr;	
   }

   qelem = queue[fd].tail;
   ptr = qelem->ptr;
   qelem->ptr = NULL;
   queue[fd].total--;
   
   prev = qelem->prev;
   if (prev) {
       prev->next = qelem->next;
       queue[fd].tail = prev;
   } else {
       massert(queue[fd].head == queue[fd].tail, __LINE__, 1);
       massert(queue[fd].total == 0, __LINE__, 1);
       queue[fd].head = queue[fd].tail = NULL;
   }

   free(qelem);
   massert(queue[fd].total > 0, queue[fd].total, 1);
  
   return ptr;
}

#if 1
void
spush (int fd, void *ptr)
{
   qelem_td *old_elem = NULL, *qelem;

   if (!verify_lib(fd, STACK)) {
       massert(0, __LINE__, 0);
       return;
   }
   
   qelem = (qelem_td *)calloc(1, sizeof(qelem_td));
   qelem->ptr = ptr;
   queue[fd].total++;
   old_elem = queue[fd].head; 
   if (old_elem) {
       qelem->next = old_elem;
   }
   queue[fd].head = qelem; 		
}

void *
spop (int fd) 
{
	qelem_td *qelem;
	void *ptr;

	if (!queue[fd].total) return NULL;

	qelem = queue[fd].head;
	if (!qelem) {
		massert(0, __LINE__, 0);
		return NULL;
	}

	queue[fd].total--;
	queue[fd].head = qelem->next;
	ptr = qelem->ptr;
	free(qelem);
	return ptr;
}

#endif
       
