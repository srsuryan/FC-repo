#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int debug = 0;

void
convert (char *ostr, char *cstr, char *ptr)
{
    int c = 0;
    char s[32] = {0}, *bstr = ostr;

    memset(s, '\0', 32);
    //printf("ostr %c cstr %c ptr %c, %ld\n", *ostr, *cstr, *ptr, cstr - ostr);
    while (ostr < cstr) {
        s[c] = *ostr;
        c++;
        ostr++;
    }
    s[c] = *ptr;
    //printf("ostr %c cstr %c ptr %c, %ld %s\n", *ostr, *cstr, *ptr, cstr - ostr, s);

    c++;
    *ptr = '\0';
    while (cstr < ptr) {
        s[c] = *cstr;
        cstr++;
        c++;
    }

    memcpy(bstr, s, strlen(s));
    if (debug) {
        printf("Covert %s %s\n", s, ostr);
    }
}

char *
get_prev_lexo (char *str, char *ptr)
{
    int max;
    char nc;
    char *maxptr = NULL;

    nc = *ptr;
    ptr++;
    max = -1;
    maxptr = ptr;
    while (*ptr != '\0') {
        if ((*ptr < nc) && (*ptr > max)) {
            maxptr = ptr;
            max = (int)*ptr;
        }
        ptr++;
    }

    if (debug) {
        printf("Choose max %c nc %c maxptr %p\n", (char)max, nc, maxptr);
    }

    return max == -1 ? NULL : maxptr;
}

int
main (int argc, char *argv[1])
{
    int i, n;
    char bstr[32], *ptr, *str;

    memcpy(bstr, "4312", 4);
    str = bstr;
    n = strlen(str);

    i = n - 2;
    do {
        ptr = get_prev_lexo(bstr, str + i);
        if (ptr) {
            convert(bstr, str + i, ptr);
            if (debug) {
                printf("bstr %s ptr %p, %c, %s\n", bstr, ptr, *ptr, ptr);
            }
            printf("lex perv perm %s\n", bstr);
            break;
        } else {
            i--;
        }
    } while (i >= 0);
}
