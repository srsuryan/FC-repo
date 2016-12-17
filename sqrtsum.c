#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/*
http://www.geeksforgeeks.org/minimum-number-of-squares-whose-sum-equals-to-given-number-n/
*/

enum {
LOW = 0,
HIGH,
MAX,
};

int debug = 0;

int 
main (int argc, char *argv[])
{
    int a[MAX] = {0}, sqcount = 0;
    int nh, n, aup, orig;

    if (argc == 1) return 1;

    n = strtol(argv[argc-1], 0, 0);
    orig = n;

    while (n > 0) {
        if (n <= 3) {
            sqcount += n;
            break;
        }

        a[HIGH] = a[LOW] = n/2;
        while (a[LOW]*a[LOW] > n) {
            a[HIGH] =  a[LOW];
            a[LOW] = a[HIGH]/2;
        }

        if (a[LOW]*a[LOW] == n) {
            sqcount++;
            if (debug) {
                printf("a[LOW] %d total sqcount %d\n ", a[LOW], sqcount);
            }
            break;
        }
        if (a[LOW] == a[HIGH]) {
            if (aup == orig) { 
                sqcount += n;
                if (debug) {
                    printf("sqcount +n = %d SQ = %d aup %d\n", n, sqcount+n, aup);
                }
                break;
            }
        }

        if (debug) {
            printf("Figured low %d and high %d for n %d aup %d\n", 
                    a[LOW], a[HIGH], n, aup);
        }

        while ((a[LOW]+1 != a[HIGH])  && (a[LOW] != a[HIGH])){
            while (a[HIGH]*a[HIGH] > n) { 
                nh = (a[HIGH]+a[LOW])/2; 
                if (nh*nh > n) {
                    a[HIGH] = nh;
                } else if (nh == n) {
                    sqcount++;
                    if (debug) {
                        printf("nh %d n %d sqcount %d\n", nh, n, sqcount);
                    }
                    return 1;
                } else {
                    a[LOW] = nh;
                    if (debug) {
                        printf("a[LOW] = %d\n", a[LOW]);
                    }
                    break;
                }
            }
        }
        sqcount++;
        aup += a[LOW]*a[LOW];
        n = n - (a[LOW]*a[LOW]);
        if (n == 1) {
            sqcount++;
            break;
        }
        if ((a[LOW]*a[LOW] == n) || 
                (a[HIGH]*a[HIGH] == n)) {
            break;
        }
    }

    printf("Minimum Square Root Count %d\n", sqcount);    
    return 0;
}
