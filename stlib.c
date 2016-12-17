#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qlib.h"

stack_td stack[LMAX] = {0};

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
stack_size (int fd)
{

   return stack[fd].total;
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

int
slib_init (ds_type type, stack_td **q, int *fdp)
{
   int rv = 0, i, fds;
   static int ss_init = 1;

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
               *q = &stack[fds];
           }
           *fdp = fds;
           rv = 1;
	  //printf("libinit %d q %p %p rv %d Q %d\n", libinit[fds], q, &stack[fds], rv, STACK);
       } else {
           rv = 0;
       }
       break;
   default:
      break;
   }
  return rv;
}


selem_td *
shead (int fd)
{
    return stack[fd].head;
}

void
spush (int fd, void *ptr)
{
   selem_td *old_elem = NULL, *selem;

   if (!verify_lib(fd, STACK)) {
       massert(0, __LINE__, 0);
       return;
   }

   selem = (selem_td *)calloc(1, sizeof(selem_td));
   selem->ptr = ptr;
   stack[fd].total++;
   old_elem = stack[fd].head;
   if (old_elem) {
       selem->next = old_elem;
   }
   stack[fd].head = selem;
}

void *
spop (int fd)
{
        selem_td *selem;
        void *ptr;

        if (!stack[fd].total) return NULL;

        selem = stack[fd].head;
        if (!selem) {
            massert(0, __LINE__, 0);
            return NULL;
        }

        stack[fd].total--;
        stack[fd].head = selem->next;
        ptr = selem->ptr;
        free(selem);
        return ptr;
}
