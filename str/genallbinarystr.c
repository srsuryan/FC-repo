#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int debug = 0;
void
gen_all_bin (char *str, char *ostr)
{
    char *mstr, *omstr;

    mstr = calloc(1, sizeof(char)*32);
    memcpy(mstr, ostr, 32);
    omstr = mstr;

    mstr = (char *)mstr + (str - ostr);
    if (debug) {
        printf("mstr %s index %d\n", mstr, (str - ostr));
        getchar();
    }
    while ((*mstr !='\0') && (*mstr != '?')) mstr++;
    
    if (*mstr == '\0') {
        printf("String %s\n", ostr);
        return;
    }

    *mstr = '0';
    gen_all_bin(mstr+1, omstr);
    *mstr = '1';
    gen_all_bin(mstr+1, omstr);
}

int 
main (int argc, char *argv[1])
{
    char *ostr = argv[1], *str = argv[1];

    if (argc <= 1) return -1;

    if (debug) {
        printf("str %s\n", ostr);
        getchar();
    }
    while ((*str !='\0') && (*str != '?')) str++;

    if (*str == '\0') return 1;

    if (debug) {
        printf("str %s index %c \n", str, *str);
        getchar();
    }

    gen_all_bin(str, ostr);

    return 0;
}

