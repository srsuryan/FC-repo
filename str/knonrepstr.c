#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_td_ {
    char i;
    struct node_td_ *prev;
    struct node_td_ *next;
} node_td;

typedef struct alpha_ {
    int count;
    node_td *node;
} alpha;

typedef struct strapp_ {
    alpha a[26];
    node_td *store;
} strapp;

strapp sdb = {0};

int debug = 0;
void
construct (char *str)
{
    node_td *node, *n, *p;
    static node_td *prev = NULL;
        
    if (!sdb.a[*str - 'a'].count) {
        node = calloc(1, sizeof(node_td));
        node->i = *str;
        node->prev = prev;
        if (prev) {
            prev->next = node;
        } else if (!prev) {
            sdb.store = node;
        }

        sdb.a[*str-'a'].count++;
        prev = node;
        if (debug) {
            printf("Node %c %d prev %p %p\n", *str, *str - 'a', prev, sdb.store);
            getchar();
        }
        sdb.a[*str -'a'].node = node;
    } else {
        node = sdb.a[*str-'a'].node;
        p = node->prev;
        n = node->next;
        if (p) {
            p->next = n;
            node->prev = NULL;
            /* Check if this also happens to be the previous node */
            if (node == prev) {
                prev = p;
            }
            if (debug) {
                printf("Node2 %c %d prev %p %p\n", *str, *str - 'a', prev, sdb.store);
                getchar();
            }
        } else {
            sdb.store = n;
            if (n) {
                n->prev = NULL;
            }
            /* Check if this also happens to be the previous node */
            if (node == prev) {
                prev = NULL;
            }
        }
        sdb.a[*str-'a'].count++;
    }
}

int 
main (int argc, char *argv[])
{
    node_td *node;
    int count = 0, k = 3;
    char *str = "geeksforgeeks";


    while (*str != '\0') {
        construct(str);
        str++;
    }

    node = sdb.store;
    while (node && count < k-1) {
        if (debug) {
            printf(" %c ", node->i);
        }
        node = node->next;
        count++;
    }
    printf("\n [%c] \n",  node->i);
}
