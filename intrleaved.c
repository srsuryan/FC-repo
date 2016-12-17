// C/C++ program to print all interleavings of given two strings
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int debug = 0;

char *
schar (char *intrls, char sc, int len, int rev)
{
    int j;

    if (rev) {
        for (j = rev; j >= 0; j--) {
            if (intrls[j] == sc) {
                return &intrls[j];
            }
        }
    } else {
        for (j = 0; j < len; j++) {
            if (intrls[j] == sc) {
                return &intrls[j];
            }
        }
    }
    return NULL;
}


int
check_intrleave (char *intrls, char *ptr, int intrlen)
{
    char *pc;
    int len;
    int ptrlen = strlen(ptr);

    pc = schar(intrls, ptr[ptrlen-1], intrlen, 0);

    if (!pc) return 0;

    while (pc && ptrlen && (pc >= intrls)) {
        len = pc - intrls;
        if (debug) {
            printf("pc %c len %d %c ptrlen %d\n", *pc, len, intrls[len], ptrlen);
            getchar();
        }
        *pc = (char)0;
        ptrlen--;
        if (!ptrlen) {
            return 1;
        }
        if (debug) {
            printf(" %c %c \n", ptr[ptrlen-1], intrls[len-1]);
        }
        pc = schar(intrls, ptr[ptrlen-1], len, len-1);
    }

    return 1;
}

int 
main (int argc, char *argv[])
{
    int  f1, f2, i;
    char str1[] = "XXY";
    char str2[] = "XXZ";
    char intrls[32] = "XXZXXY";
    int intlen = strlen(intrls);

    f1 = check_intrleave(intrls, str1, intlen);
  
    if (!f1) {
        printf("Not Intrleaved\n");
        return 1;
    }
    f2 = check_intrleave(intrls, str2, intlen);
    if (!f2) {
        printf("Not Intrleaved\n");
        return 1;
    }
    for (i = 0; i < intlen; i++) {
         if (intrls[i] != (char)0) {
             printf("Not Intrleaved\n");
             return 1;
         }
    }
    printf("Intrleaved\n");
    return 0;
}

