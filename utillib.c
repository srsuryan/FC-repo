#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "qlib.h"
#include "util.h"
int *   
get_from_main (int argc, char *argv[])
{

    int *a, i = 0, j;

    a = (int *) calloc(1, sizeof(int)*32);
    for (i = 1; i <= argc -1; i++) {
         j = strtol(argv[i], 0, 0);
//       printf("j %d\n", j);
         a[i-1] = j;
    }
    for (; i < 32; i++) 
        a[i-1] = INVALID;
    return a;   
}

int 
find_min (int *a, int max)
{
   int i, min;
 
   min = a[0];
   for (i = 1; i < max; i++) {
	if (min > a[i]) {
	    min = a[i];
	}
    }
    return min;
}

int 
find_max (int *a, int max)
{
   int i, maxv = -1;
 
   maxv = a[0];
   for (i = 1; i < max; i++) {
        if (maxv < a[i]) {
            maxv = a[i];
        }
    }
    return maxv;
}
	
