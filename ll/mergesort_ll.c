
sll *
mergesort_ll (sll *p1, sll *n1, sll *p2, 
             sll *n2, sll **cln)
{

     sll *s1 = NULL;

     if (!n1 || !n2) return;

     n2->next = NULL;
     n1->next = NULL;

     if (!p1 && !p2) {
         /* Case of 2 node comparison */
         if (n1->i > n2->i) {
             n2->next = n1;
             *cln = n1;
             return n2;
         } else {
             *cln = n2;
             return n1;
         }
    } else if (p1 && !p2) {
        /* Case of 3 node comparison */
        s1 = n1;
        if (p1->i > n2->i) {
            s1 = n2;
            n2->next = p1;
        }
        *cln = n1;
        return s1;
    } else if (p1 && p2) {
        /* Case of 4 and above */
        while (p1 && p2) {
            if (p1->i > p2->i) {
                if (!s1) {
                    s1 = p2;
                    p2 = p2->next;
                    s1->next = NULL;
                    l1 = &s1->next;
                } else {
                    *l1 = p2;
                    l1 = &p2->next;
                    p2 = p2->next;
                    *l1 = NULL;
                }
            } else {
                if (!s1) {
                    s1 = p1;
                    p1 = p1->next;
                    s1->next = NULL;
                    l1 = &s1->next;
                } else {
                    *l1 = p1;
                    l1 = &p1->next;
                    p1 = p1->next;
                    *l1 = NULL;
                }
            }

            if (p1) {
                *l1 = p1;
            } else {
                *l1 = p2;
            }
            node = *l1;
            while (node) {
                tempn = node;
                node = node->next;
            }
        }
        if (debug) {
            printf("Case of 4 or above node comparision (%d %d %d %d)\n", 
                    p1 ? p1->i : -1, n1 ? n1->i : -1, p2 ? p2->i : -1, n2 ? n2->i : -1);
            print_sl(s1);
            getchar();
        }

    }

    *cln = tempn;
    return s1;
}

void
split (sll *p1, sll *n1, sll *p2, sll *n2, int diff)
{

    if (diff == 2) {
    } else if (diff == 3) {
    } else {
       n1 = p1;
       n2 = p1->next;
       c = 0;
       while ((n1 != p2) && (n2)) {
           prev1 = n1;
           n1 = n1->next;
           c++;
           prev2 = n2;
           n2 = n2->next;
           if (!n2) break;
           n2 = n2->next;
       }
       n1 = prev1;
       p2 = n1->next;
       n2 = prev2;
       split(p1, n1, p2, n2, c);
    }
}
