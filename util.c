
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "qlib.h"

int *
get_from_main (int argc, char *argv[])
{

    int *a, i = 0, j;

    a = (int *) calloc(1, sizeof(int)*32);
    for (i = 1; i <= argc -1; i++) {
	 j = strtol(argv[i], 0, 0);
//	 printf("j %d\n", j);
	 a[i-1] = j;
    }
    for (; i < 32; i++) 
	a[i-1] = 0xFFFF;
    return a;	
}
  
