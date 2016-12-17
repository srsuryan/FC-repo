#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum dir_ {
    NONE = 0,
    HORIZONTAL,
    VERTICAL,
} dir;

typedef struct sll_
{
    int x, y;
    struct sll_ *next;
} sll;
 
sll *start = NULL, *start2 = NULL;
/* Function to insert a node at the beginning */
void push(sll ** head_ref, int x,int y)
{
    sll* new_node = 
           (sll*) malloc(sizeof(sll));
    new_node->x  = x;
    new_node->y  = y;
    new_node->next = (*head_ref);
    (*head_ref)  = new_node;
}
 
/* Utility function to print a singly linked list */
void printList(sll *head)
{
    sll *temp = head;
    while (temp != NULL)
    {
        printf("(%d,%d)-> ", temp->x,temp->y);
        temp = temp->next;
    }
    printf("\n");
 
}

dir
get_line_type (sll *p, sll *m)
{

    if (p->x == m->x) return VERTICAL;
    return HORIZONTAL; 
}


int 
main (int argc, char *argv[])
{
    sll *head = NULL, *c, *p, *m, *temp;
    int line_type, min_x = -1, max_x, min_y = -1, max_y;
    dir clt = NONE;

    push(&head, 50,10);
    push(&head, 11,10);
    push(&head, 9,10);
    push(&head, 7,10);
    push(&head, 7,9);
    push(&head, 7,8);
    push(&head, 7,7);
    push(&head, 7,6);
#if 0
    push(&head, 5,10);
    push(&head, 1,10);
    push(&head, 0,10);
#endif
    printf("Given Linked List: \n");
    printList(head);
    getchar();

    start = head;

    c = NULL;
    p = start;
    if (!p) return 1;
    m = p->next;
    c = m ? m->next : NULL;
    
    line_type = get_line_type(p, m);
    while (m && c) {
        if (line_type == HORIZONTAL) {
            if (clt == VERTICAL) {
                p->next = temp;
                temp->next = NULL;
                start2 = m;
                p = m;
                m = m->next;
                c = m ? m->next : NULL;
                if (!c) break;
            printf("TRANSIENT (%d %d) (%d %d) (%d %d) :: Temp (%d %d)\n", p->x, p->y, m->x, m->y, 
                    c ? c->x  : -1, c ? c->y : -1, temp->x, temp->y);
            getchar();
            }

            clt = HORIZONTAL;
            if (min_x == -1) {
                min_x = p->x;
            }
            max_x = m->x;
            p->next = c;
            temp = m;
            m = c;
            c = c->next;
            printf("H (%d %d) (%d %d) (%d %d)\n", p->x, p->y, m->x, m->y, c ? c->x  : -1, c ? c->y : -1 );
            getchar();
        } else {
            if (clt == HORIZONTAL) {
                p->next = temp;
                temp->next = NULL;
                start2 = m;
                p = m;
                m = m->next;
                c = m ? m->next : NULL;
                if (!c) break;
            }
            clt = VERTICAL;
            if (min_y == -1) {
                min_y = p->y;
            }
            max_y = m->y;
            p->next = c;
            temp = m;
            m = c;
            c = c->next;
            printf("V (%d %d) (%d %d) (%d %d) :: Temp (%d %d)\n", p->x, p->y, m->x, m->y, 
                    c ? c->x  : -1, c ? c->y : -1, temp->x, temp->y);
            getchar();
        }
        line_type = get_line_type(temp, m);
    }
    printList(start);
    printList(start2);
}
