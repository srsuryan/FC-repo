#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../ll/util.h"

void
find_range (int i, int *minl, int *maxr, int match, int *a)
{
    *minl = *maxr = -1;

    while (i >= 0) {
        if (match < a[i]) {
            if (*maxr == -1) {
                *maxr = i;
            } else if (*maxr > a[i]) {
                *maxr = a[i];
            }
        } else {
            if (*minl == -1) {
                *minl = a[i];
            } else if (*minl < a[i]) {
                *minl = i;
            }
        }
        i--;
    }
}

int
main (int argc, char *argv[])
{
    int *a, i, minr, maxr;

    a = get_from_main(argc, argv);

    i = 1;
    while (a[i] != INVALID) {
        find_range(i-1, &minr, &maxr, a[i], a);
        printf("Range check for %d %d %d\n", a[i], (minr != -1) ? a[minr] : -1, 
                (maxr != -1) ? a[maxr] : -2);
        i++;
    }
}
