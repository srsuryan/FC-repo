#include <stdio.h>
#include <string.h>

int
max (int i, int j)
{
    if (i > j) return i;
    return j;
}

void
lcs (char *x, char *y, int m, int n)
{
    char ll[32] = {0};
    int LCS[m+1][n+1], i, j, k = 0;

    for (i = 0; i <= m; i++) {
        for (j = 0; j <= n; j++) {
            if (!i || !j) {
                LCS[i][j] = 0;
                continue;
            }

            if (x[i-1] == y[j-1]) {
                LCS[i][j] = 1 + LCS[i-1][j-1];
                ll[LCS[i][j]] = x[i-1];
#if 0
                if ((j-1) && (LCS[i][j] > LCS[i][j-1])) {
                    ll[k] = x[i-1];
                    k++;
                }
#endif
            } else {
                LCS[i][j] = max(LCS[i][j-1], LCS[i-1][j]); 
            }
        }
    }

    for (i = 0; i <= m; i++) {
        for (j = 0; j <= n; j++) {
            printf(" %d ", LCS[i][j]);
        }
        printf("\n");
    }

    printf("ll %c%c%c%c%d --%s\n", ll[0], ll[1], ll[2], ll[3], ll[4], ll);
}

/* Driver program to test above function */
int main()
{
  char X[] = "AGGTAB";
  char Y[] = "GXTXAYB";
  int m = strlen(X);
  int n = strlen(Y);
  lcs(X, Y, m, n);
  return 0;
}
