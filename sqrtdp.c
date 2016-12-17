#include <stdio.h>
#include <stdlib.h>

int debug = 0;

int
min (int a, int b)
{

    if (a < b) return a;
    return b;
}

void
get_dpn (int dp[], int count, int *f)
{
    int i, c;

    i = count;
    c = 2;
    dp[count] = dp[count-1]+1;
    while (c <= i) {
        if (count == dp[c]*dp[c]) {
            dp[count] = 1;
            *f = 1;
            return;
        }
        dp[count] = min(dp[count], dp[count - c]+dp[c]);
        c++;
    }
    if (dp[count] == 1) {
        *f = 1;
    } else {
        *f = 0;
    }
}

int
main (int argc, char *argv[])
{
    int i, dp[32] = {0}, v, last, f, count;

    //if (argc <= 1) return 1;

    //v = strtol(argv[1], 0, 0);

    v = 18;
    dp[1] = 1;
    dp[2] = 2;
    dp[3] = 3;
    dp[4] = 1;
    f = 1;
    last = 4;
    count = 4;
    while (count <= v) {
        if (f) last = count;
        while (f && (f <= 3) && (count+f <= v)) {
            dp[count+1] = dp[last] + f; //5, 6, 7
            f++;
            count++;
        }
        if (count == v) {
            printf("count %d v %d\n", count, v);
            getchar();
            break;
        }
        get_dpn(dp, count+1, &f);
        count++;
    }


    for (i = 0; i < v; i++) {
        if (debug) {
            printf("dp[count = %d] = %d\n", i, dp[i]);
        }
    }
    printf("dp[count = %d] = %d\n", v, dp[v]);

    return 0;
}

