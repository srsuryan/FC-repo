#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int debug = 1;

void
conv_str (char *s1, char *s2, int pos, int s1n)
{
    int i;
    char temp;

    memset(s2, '\0', 32);
    i = s1n -1;
    while (i > pos) {
        s2[i] = s1[i];
        i--;
    }

    temp = s1[i];
    while (i > 0) {
        s2[i] = s1[i-1];
        i--;
    }
    s2[0] = temp;
}

int
get_str_len (char *src, int *ac)
{
    int count = 0;

    while (*src != '\0') {
        ac[*src-'A']++;
        src++;
        count++;
    }

    return count;
}

int
check_with_orig (char dst, int *ac)
{
    if (ac[dst - 'A']) {
        ac[dst-'A']--;
        return 1;
    }
    return 0;
}

int
main (int argc, char *argv[])
{
    char *src = argv[1], *dst = argv[2];
    int n, i = 0, ac[26] = {0}, minop = 0;
    char s2[32] = {0};

    if (argc <= 2) return 1;

    n = get_str_len(src, ac);
    while (dst[i] != '\0') {
        if (check_with_orig(dst[i], ac)) {
            n--;
        } else {
            printf("Invalid strings %s %s\n", src, dst);
            return 0;
        }
        i++;
    }
    
    if (n) {
        printf("Invalid strings 2 %s %s\n", src, dst);
        return 0;
    }

    n = strlen(argv[1]);
    memcpy(s2, src, n);
    do {
        i = n-1;
        while ((i >= 0) && (s2[i] == dst[i])) {
            i--;
        }

        if (i < 0) {
            printf("Matches \n");
            return 0;
        }

        conv_str(src, s2, i, n);
        if (debug) {
            printf("s1 %s s2 %s i %d n %d\n", src, s2, i, n);
            getchar();
        }
        minop++;

        memcpy(src, s2, n);
        if (!strcmp(src, dst)) {
            printf("Matches src and dst  %s %s minop %d\n", src, dst, minop);
            break;
        }
    } while (1);
}

