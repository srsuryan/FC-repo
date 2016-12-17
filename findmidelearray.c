#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "qlib.h"

/* 
 *  8 1 3 4 
 *  4 1 3 8
 *  3 1 8 1
 *  4 2 1 1 4
 */

int
main (int argc, char *argv[])
{
    int *a, max;
    int i, j, sumi, sumj;

    a = get_from_main(argc, argv);

    i = 0;
    max = argc - 2;
       
    printf(" %d %d max val %d\n", a[i], max, a[max]);
    getchar();
    sumi = a[i];
    sumj = a[max];
    for (i = 0, j = max -1; i < j; ) {
         while (sumi < sumj) {
             sumi += a[i];
             i++;
             continue;
         }

         while (sumj < sumi) {
             sumj += a[j];
             j--;
             continue;
        }

        if (sumi == sumj) {
            i++; j--;
        }
    }

    if (i >= j) {
        if (sumi == sumj) {
            printf("Array is eq at element %d idx %d \n", a[i-1], i-1);
        } else {
            printf(" Does not have eq sumi %d sumj %d %d %d\n", sumi, sumj, i, j);
        }
    }
}


