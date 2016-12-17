#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qlib.h"

int debug = 0;

typedef struct rect_td_ {
	int idx;
	int val;
} rect_td;

int
largestrect (int *a, int max)
{
	rect_td *rect, *inrect, *save_rect;
	int rv, fd, i, idx, area, save_idx, next_idx, larea = -1;
	stack_td *s;
	selem_td *selem, *pop_selem;

        rv = slib_init(STACK, &s, &fd);
        if (!rv || !s) {
            printf("Lib init failed %d %p\n", rv, s);
            return 1;
        }
	
	rect = calloc(1, sizeof(rect_td));
	rect->idx = 0;
	rect->val = a[0];
	spush(fd, rect);
	i = 1;
        while (i < max) {	
	    selem = (selem_td *)shead(fd);
	    if (!selem) break;
	    inrect = (rect_td *)selem->ptr;
		
	    rect = calloc(1, sizeof(rect_td));
	    rect->idx = i;	    
	    rect->val = a[i];
	    save_rect = rect; 
	    save_idx = i;
	    if (debug) {
	        printf("1. (idx %d val %d) (%d %d) %d\n", 
			inrect->idx, inrect->val, i, a[i], stack_size(fd));
	    }
	    while (rect && inrect && (rect->val < inrect->val) && stack_size(fd)) {
		rect = (rect_td *)spop(fd);
		if (debug) {
		    printf("2. POP (idx %d val %d) (idx %d val %d) size %d\n", 
			rect->idx, rect->val, inrect->idx, inrect->val,
			stack_size(fd));
		}
	    	selem = (selem_td *)shead(fd);
	    	if (!selem) {
		    area = rect->val * (save_idx - rect->idx);
		    if (area > larea) larea = area;
		    if (debug) {
		        printf("2.b area %d i = %d %d\n", area, i, rect->idx);
		    }
		    break;
		}
	    	inrect = (rect_td *)selem->ptr;
		area = rect->val*(save_idx - inrect->idx - 1);
		if (area > larea) larea = area;
		if (debug) {
		    printf("2.c POP (idx %d val %d)  (%d %d) size %d area %d (%d %d %d)\n", 
			inrect->idx, inrect->val, rect->idx, rect->val,
			 stack_size(fd), area, i, rect->idx, idx);
	        }
		rect = save_rect;
	    }
	    spush(fd, save_rect);
	    i++;
	}

	save_idx = i;
        if (debug) {
	    printf("Stack has \n");
	}
	rect = spop(fd);
	while (rect) {
	   //printf(" %d %d \n", rect->idx, rect->val);
	   if (stack_size(fd)) {
	       selem = (selem_td *)shead(fd);
	       inrect = (rect_td *)selem->ptr;
	       next_idx = inrect->idx;
	   } else {
	       next_idx = 0;
	   }
	   area = rect->val*(save_idx - next_idx - (next_idx ? 1 : 0));
	   if (debug) {
	       printf("POPED area %d:: val %d :: sidx %d :: nidx %d:: Total %d\n", area, rect->val, save_idx, next_idx,
			rect->val*(save_idx-next_idx - (next_idx ? 1 : 0)));
	   }
	   if (area > larea) larea = area;
	   rect = spop(fd);
	}

	printf("Largest area %d\n", larea);
	return larea;
}
