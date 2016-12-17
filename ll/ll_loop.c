#include <stdio.h>
#include "ll.h"
#include "util.h"

int
check_loop (sll *n, sll *start)
{
    int count = 0;

    while (start) {
        if (start != n) {
            count++;
        } else {
            return count;
        }
        start = start->next;
    }

    return count;
}

int
check_loop2 (sll *start, int inc, sll *n, int *lat)
{
    int c = 1;
    
    while (start != n) {
        start = start->next;
        c++;
    }

    if (start == n) {
        if (c != inc) {
            *lat = c;
            return 1;
        }
        return 0;
    }

    return c;
}

int 
check_loop3 (sll *s, sll *n)
{

    while (1) {
        if (s == n) return 1;

        s = s->next;
        n = n->next;
        if (!n) return 0;
        n = n->next;
    }

}

int 
main (int argc, char *argv[])
{
    sll *p, *prev, *s, *start, *n;
    int loop, *a, rc, pc = -1, c, lat = 1;

    a = get_from_main(argc, argv);
    p = create_list(a);

    s = p;
    start = s;
    while (s) {
        prev = s;
        s = s->next;
    }

#if 0    
    s = p;
    s = s->next;
    s = s->next;
    s = s->next;
    prev->next = s;
    p = start;
    while (p) {
        rc = check_loop(p->next, start);
        if (rc < pc) {
            printf(" loop at %d\n", p->i);
            return 1;
        } else {
            pc = rc;
        }
        p = p->next;
    }

    c = 1;
    n = start->next;
    if (start == n) {
        loop = 1;
        goto end;
    }

    while (n) {
        c++;
        lat = 0;
        loop = check_loop2(start, c, n, &lat);
        if (loop) break;
        n = n->next;
    }
#endif

    loop = check_loop3(start, start->next);
//end:
    printf(" loop %s at %d\n", loop ? "detected" : " not detected", lat);
    return 0;
}
