#include <stdio.h>
#include <stdlib.h>

int debug = 1, max_apd;
int b[512] = {0};

int 
seq_has_ap (int *a, int max)
{
    int i, j, k, apd, mapd = -1;

    for (j = 1; j < max-1; j++) {
         
        i = j - 1;
        k = j+1;

        if (debug) {
            printf("Start %d %d %d\n", i, j, k);
        }
        while ((i >= 0) && (k <= max-1)) {
            if (a[i]+a[k] >  2*a[j]) {
                if (debug) {
                    printf("INC a[%d] %d + a[%d] %d = 2*a[%d] %d\n", i, a[i], k, a[k], j, 2*a[j]);
                }
                i--;
            } else if (a[i]+a[k] < 2*a[j]) {
                if (debug) {
                    printf("DEC a[%d] %d + a[%d] %d = 2*a[%d] %d\n", i, a[i], k, a[k], j, 2*a[j]);
                }
                k++;
            } else {
                apd = abs(a[i] - a[k])/2;
                b[apd]++;
                if (mapd < b[apd]) {
                    mapd = b[apd];
                    max_apd = apd;
                }
                if (debug) {
                    printf("MAT: a[%d] %d + a[%d] %d = 2*a[%d] %d\n", i, a[i], k, a[k], j, 2*a[j]);
                    getchar();
                }
                break;
            }
        }
    }

    return 0;
}

int
main ()
{
//   int a[] = { 1, 7, 10, 15, 27, 29};
   //int a[] = { 1, 7, 9, 15, 20, 25, 29, 30, 43, 57, 71};
    int a[] = { 2, 3, 4, 5, 6, 4};
    int i, n = sizeof(a)/sizeof(int);

    printf(" %s sequence\n", seq_has_ap(a, n) ? "Has" : "No");
    printf(" m_apd %d count %d\n", max_apd, b[max_apd]);
    for (i = 0; i < n; i++) {
         if (b[i]) {
             printf(" b[%d] = %d\n", i, b[i]);
         }
     }
}

