#include <stdio.h>
#include <string.h>

int debug = 1;
/*
 * Find if a given string can be represented from a substring by iterating the substring “n” times
 */


int
strrepeat (char *str, char *substr, int nsub)
{
    int rv;
    if (*str == '\0') return 1;

    if (!strncmp(str, substr, nsub)) {
        rv = strrepeat(str+nsub, substr, nsub);
        if (debug) {
            printf(" rv %d str %s substr %s nsub %d\n", rv, str+nsub, substr, nsub);
            getchar();
        }
        return rv;
    }
    return 0;
}

int
main (int argc, char *argv[])
{
    int rv = 0, nsub, n;
    char substr[32];
    char *str = argv[1];

    if (argc <= 1) return 1;

    memset(substr, '\0', 32);
    substr[0] = str[0];
    nsub = 1;
    n = strlen(str);

    while (!rv && strlen(substr) <= n/2) {
        rv = strrepeat(str+nsub, substr, nsub);
        if (rv) {
            printf("substring %s \n", substr);
            break;
        }
        substr[nsub] = str[nsub];
        nsub++;
        if (debug) {
            printf("now check for %s nsub %d\n", substr, nsub);
            getchar();
        }
    }

    if (!rv) {
        printf("not found\n");
    }
}
