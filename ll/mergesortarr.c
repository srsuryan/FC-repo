
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

int debug = 1;

void
swap (int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void
greatof3 (int e, int s, int *a, int *f, int *b, int *c)
{
    int a1, a2, a3;

    a1 = *f = a[s];
    a2 = *b = a[s+1];
    a3 = *c = a[s+2];
    if (a1 > a2) {
        if (a1 > a3) {
            *c = a1;
            if (a2 > a3) {
                *b = a2;
                *f = a3;
            } else {
                *b = a3;
                *f = a2;
            }
        } else {
            *c = a3;
            *b = a1;
            *f = a2;
        }
    } else if (a2 > a3) {
        *c = a2;
        if (a2 > a1) {
            *b = a2;
            *f = a1;
        } else {
            *b = a1;
            *f = a3;
        }
    }
    printf("greatest between (%d %d %d) is (%d %d %d)\n",
            a1, a2, a3, *f, *b, *c);
}

void
print_arr (int *a, int si, int ei, char b)
{
    int i = si, count = 0;

    printf("%c-max %d si %d ei %d \n", b, (ei - si +1), si, ei);
    while (count < (ei - si +1)) {
        printf("%c[%d] = %d ", b, i, a[i]);
        i++;
        count++;
    }
    printf("\n");
}

void
msort (int *a, int si, int ei)
{
    int diff, mid, i, j, k, a1, a2, a3;
    int b[32] = {0};

    diff = ei - si + 1;
   
    if (diff == 1) return;
 
    if (debug) {
        printf("ei %d si %d diff %d\n", ei, si, diff);
        getchar();
    }

    if (diff == 2) {
        if (a[ei] < a[si]) {
            swap(&a[ei], &a[si]);
        }
        return;
    } else if (diff == 3) {
        greatof3(ei, si, a, &a1, &a2, &a3);
        a[si] = a1;
        a[si+1] = a2;
        a[si+2] = a3;
        if (debug) {
            printf("ei %d si %d mid %d size %d (%d %d %d)\n", 
                    ei, si, (ei-si+1)/2, (ei-si+1), a[si], a[si+1], a[si+2]);
            getchar();
        }
        return;
    } else {
        mid = (ei - si +1)/2;
        
        i = si;
        j = mid+1;
        msort(a, si, mid);
        msort(a, mid+1, ei); 
        if (debug) {
            printf("ei %d si %d mid %d size %d\n", ei, si, mid, (ei-si+1));
            print_arr(a, si, mid, 'K');
            print_arr(a, mid+1, ei, 'M');
            getchar();
        }
        while ((i <= mid) && (j <= ei)) {
            if (a[i] > a[j]) {
                b[k] = a[j];
                j++;
            } else {
                b[k] = a[i];
                i++;
            }
            k++;
        }

        while (i <= mid) {
            b[k] = a[i];
            k++; 
            i++;
        }

        while (j <= ei) {
            b[k] = a[j];
            k++;
            j++;
        }
        memcpy(&a[si], b, sizeof(int)* (ei - si +1));
        if (debug) {
            print_arr(a, si, ei, 'a');
            print_arr(b, 0, (ei - si), 'b');
            getchar();
        }
    }
}

int
main (int argc, char *argv[])
{
    int *a, flip = 1;

    printf("argc %d\n", argc);
    getchar();
    a = get_from_main(argc, argv);

    msort(a, 0, argc -2);
    print_arr(a, 0, argc-2, 'f');
}

