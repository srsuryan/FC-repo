#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INVALID 0xFFFFFFFF
#define TRUE 1
#define FALSE 0

int *
get_from_main (int argc, char *argv[]);
int     
find_min (int *a, int max);
int 
find_max(int *a, int max);
