#include <stdio.h>
#include <string.h>

int fact[32] = {0};
int rank[32] = {0};

int debug = 1;

void
calc_fact (int n)
{
    int i;

    fact[0] = 0;
    fact[1] = 1;

    for (i = 2; i < n; i++) {
        fact[i] = fact[i-1]*i;
        if (debug) {
            printf("Fact[%d] = %d\n", i, fact[i]);
        }
    }
}

void
set_rank (char *str)
{
    int j, i = 1;

    rank[0] = 1;

    while (str[i] !='\0') {
        rank[i] = 1;
        for (j = i-1; j >= 0; j--) {
            if (str[j] > str[i]) {
                rank[j] += 1;
            } else {
                rank[i] += 1;
            }
        }
        i++;
    }

    if (debug) {
        for (i = 0; i < strlen(str); i++) {
            printf("Rank of %c is %d\n", str[i], rank[i]);
        }
    }
}

int
lexrank (char *str, int i, int n)
{
    int sum = 0, r;

    if ((n - 1 - i) <= 0) return 0;
    
    r = (rank[i] - 1 - i) < 0 ? 0 : (rank[i] - 1 -i);
    if (debug) {
        printf("Lextank i %dfor %c %d r %d fact %d\n", i, str[i], (rank[i] - i - 1), r, fact[n-1-i]);
    }
    
    return (r*fact[n-1-i] +
            lexrank(str, i+1, n));
}

int
main (int argc, char *argv[])
{
    int i, n;
    char *str;

    if (argc <= 1) return 1;

    str = argv[1];
    n = strlen(str);
    calc_fact(n);
    set_rank(str);
    getchar();
    printf("Lexcograph %d\n", lexrank(str, 0, n));
}
