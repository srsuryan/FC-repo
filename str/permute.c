#include <stdio.h>
#include <string.h>

void
swap (char *str, int i, int j)
{
    char temp = str[i];

    str[i] = str[j];
    str[j] = temp;
}

void
permute (char *str, int i, int n, int c)
{
 int j;

    if (i >= n) return;

    for (; i < n; i++) {
        for (j = i+1; j < n; j++) {
            swap(str, i, j);
            printf("[%d] pemute  %s\n", c, str);
            permute(str, i+1, n, (c+1));
            swap(str, j, i);
        }
    }
}

int 
main (int argc, char *argv[])
{
    char *str;
    int i, j, n, c;

    if (argc <= 1) return 1;

    n = strlen(argv[1]);
    str = argv[1];
    printf("String %s len %d\n", argv[1], n);
    for (i = 0; i < n; i++) {
        for (j = i+1; j < n; j++) {
            swap(str, i, j);
            printf("pemute  %s\n", str);
            permute(str, i+1, n, c);
            swap(str, j, i);
        }
    }
}
