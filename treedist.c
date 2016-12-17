#include <stdio.h>



int
getmindist (node_td *node, int s1, int s2, int *c, int found)
{
    int myc;

    if (!node) return FALSE;

    myc = *c;
    rv = getmindist(node->left, s1, s2, *c);

    if (rv) return *c;

    if ((node->i == s1) || (node->i == s2)){
        (*c)++;
        found++;
        if (found == 2) return TRUE;
    } else if (*c) {
        (*c)++;
    }

    rv = getmindist(node->right, s1, s2, *c);

    if (rv) retuen *c;

    if (myc) {
        *c = myc;
    }
    
    return FALSE;
}

    
