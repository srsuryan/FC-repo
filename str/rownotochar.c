#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void
col_str (char *str, int q, int r, int *idx)
{

    if (!q && r) {
        str[*idx] = 'A' + r - 1;
        return;
    } else if (!q && !r) {
        if (*idx) return;
        str[*idx] = 'Z';
        return;
    }

    if (!r) {
        str[*idx] = 'Z';
        q--;
        if (!q) return;
    }

    if (q <= 26) {
        str[*idx] = 'A' + q - 1;
        (*idx)++;
        str[*idx] =  r ? ('A' + r - 1) : 'Z';
        return;
    } else {
        str[*idx] = 'A';
       // *idx++;
        //str[*idx] =  r ? ('A' + r - 1) : 'Z';
    }

    //(*idx)++;
    col_str(str, q/26, q%26, idx);
    (*idx)++;
    str[*idx] =  r ? ('A' + r - 1) : 'Z';
}

int
main (int argc, char *argv[])
{
    char str[32] = {0};

    int idx = 0, val = strtol(argv[1], 0, 0);
    
    if (argc <= 1) return 1;
    col_str(str, val/26, val%26, &idx);
    printf("str %s \n", str);
}
