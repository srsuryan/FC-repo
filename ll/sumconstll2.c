#include <stdio.h>
#include "ll.h"
#include "util.h"

int debug = 1;

sll *
sum_ll (sll *n1, sll *n2)
{
    sll *s1 = NULL, *s2 = NULL, *mx = NULL;
    sll **last1, **last2, **lastmx, *temp, *p1, *p2;
    int sum1 = 0, sum2 = 0;

    while (n1 && n2) {

        if (n1->i < n2->i) {
            sum1 += n1->i;
            if (!s1) {
                s1 = n1;
                last1 = &s1->next;
            } else {
                *last1 = n1;
                last1 =  &n1->next;
            }
            p1 = n1;
            n1 = n1->next;
        } else if (n2->i < n1->i) {
            sum2 += n2->i;
            if (!s2) {
                s2 = n2;
                last2 = &s2->next;
            } else {
                *last2 = n2;
                last2 = &n2->next;
            }
            p2 = n2;
            n2 = n2->next;
        } else {
            printf("%d %d\n", sum1, sum2);
            p1 = n1;
            p2 = n2;
            n1 = n1->next;
            n2 = n2->next;
            if (sum1 > sum2) {
                if (!mx) {
                    mx = s1;
                    lastmx = &p1->next;
                } else {
                    *lastmx = s1;
                    lastmx = &p1->next;
                }
                p1->next = NULL;
                s1 = n1;
                if (debug) {
                    printf("check1\n");
                    print_sl(mx);
                    print_sl(s1);
                    getchar();
                }
                while (s2 != n2) {
                    temp = s2;
                    printf("Free s2 %d\n", s2->i);
                    s2 = s2->next;
                    free(temp);
                }
                print_sl(mx);
                getchar();
            } else {
                if (!mx) {
                    mx = s2;
                    lastmx = &p2->next;
                } else {
                    printf("s2 %d p2 %d\n", s2->i, p2->i);
                    *lastmx = s2;
                    lastmx = &p2->next;
                }
                p2->next = NULL;
                s2 = n2;
                if (debug) {
                    printf("check2\n");
                    print_sl(mx);
                    print_sl(s2);
                    getchar();
                }
                while (s1 != n1) {
                    temp = s1;
                    s1 = s1->next;
                    free(temp);
                }
            }
            sum1 = sum2 = 0;
            s1  = NULL;
            s2  = NULL;
            printf(" NN1 %d n2 %d\n", n1->i, n2->i);
            getchar();
        }
    }
    print_sl(n1);
    print_sl(s2);
    s1 = s1 ? s1 : n1;
    s2 = s2 ? s2 : n2;
    n1 = s1;
    n2 = s2;
    sum1 = sum2 = 0;
    while (n1) {
        sum1 += n1->i;
        n1 = n1->next;
    }
    while (n2) {
        sum2 += n2->i;
        n2 = n2->next;
    }
    if (sum1 > sum2) {
        *lastmx = s1;
    } else {
        *lastmx = s2;
    }
    printf(" sum %d %d\n", sum1, sum2);
    getchar();
    return mx;
}

int
main (int argc, char *argv[])
{
    sll *start, *s2 = NULL, *node;
    int *a;

    a = get_from_main(argc, argv);
    start = create_list(a);
    
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
    node = sum_ll(s2, start);
    print_sl(node);
    return 1;
}
