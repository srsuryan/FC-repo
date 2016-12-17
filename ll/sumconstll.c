#include <stdio.h>
#include "ll.h"
#include "util.h"

int b[2][32];


void
maxsum (int v, int dw)
{
    static int n1c = 0, n2c = 0, c, sum1 = 0, sum2 = 0;
 
    if (dw == 0) {
        b[0][n1c] += v;
        n1c++;
    } else if (dw == 1) {
        b[1][n2c] += v;
        n2c++;
    } else if (dw == 2) {
        b[0][n1c] += v;
        b[1][n2c] += v;
        n1c++;
        n2c++;
    } else if (dw == 3) {
        /* Consolidate */
        c = 0;
        while (c < n1c) {
            sum1 += b[0][c];
            c++;
        }

        c = 0;
        while (c < n2c) {
            sum2 += b[1][c];
            c++;
        }
        n1c = n2c = 0;
        b[0][n1c] = sum1 > sum2 ? sum1 : sum2;
        b[0][n2c] = sum1 > sum2 ? sum1 : sum2;
        n1c = n2c = 1;
    }
        
}

int
sum_ll (sll *n1, sll *n2)
{
    sll *s = NULL, **last;
    int pick_n1, pick_n2, sum = 0, switchen = 0;

    pick_n1 = 1;
    while (n1 && n2) {

        if (n1->i < n2->i) {
            if (pick_n1) {
                sum += n1->i;
                printf("n1 %d SUM %d ", n1->i, sum);
                getchar();
            } else if (switchen) {
                maxsum(n1->i, 0);
            }

            if (!s) {
                s = n1;
                last = &s->next;
            } else {
                *last = n1;
                last =  &n1->next;
            }
            n1 = n1->next;
        } else if (n2->i < n1->i) {
            if (pick_n2) {
                sum += n2->i;
                printf("n2 %d SUM %d", n2->i, sum);
                getchar();
            } else { 
                maxsum(n2->i, 1);
            }

            if (!s) {
                s = n2;
                last = &s->next;
            } else {
                *last = n2;
                last = &n2->next;
            }
            n2 = n2->next;
        } else {
            if (!switchen) {
                sum += n1->i;
            }
            printf("EQ %d pick_n1 %d pick_n2 %d SUM %d", n1->i, pick_n1, pick_n2, sum);
            getchar();
            if (pick_n1) {
                pick_n1 = 0;
                pick_n2 = 0;
            } else if (pick_n2) {
                pick_n2 = 0;
                pick_n1 = 0;
            }
            maxsum(0, 3);
            switchen = 1;
            maxsum(sum, 2);

            if (!s) {
                s = n1;
                s->next = n2;
                last = &n2->next;
            } else {
                *last = n1;
                last = &n1->next;
                n1 = n1->next;
                *last = n2;
                last = &n2->next;
                n2 = n2->next;
            }
            printf(" n1 %d n2 %d\n", n1->i, n2->i);
            getchar();
        }
    }
    return sum;
}

int
main (int argc, char *argv[])
{
    sll *start, *s2 = NULL, *node;
    int *a;

    a = get_from_main(argc, argv);
    start = create_list(a);
    
    memset(b, 0, sizeof(int)*32*2);
    node = start;
    while (node && node->i != 255) {
        node = node->next;
    }

    if (!node) return 1;
    s2 = node->next;
    node->next = NULL;
    print_sl(start);
    print_sl(s2);
    getchar();
    printf("Total sum %d\n", sum_ll(start, s2));
    maxsum(0, 3);
    printf("Max sum is %d %d\n", b[0][0], b[1][0]);
    return 1;
}
