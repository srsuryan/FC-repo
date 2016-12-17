#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void
print_col_str (char *str, int n)
{
    int r, count = 0;

    while (n > 0) {
        r = n%26;
        n = n/26;

        if (!r && n) {
            str[count] = 'Z';
            count++;
            n--;
            if (n) {
                str[count] = 'A' + n -1;
                count++;
                n = n/26;
            }
        } else if (r && !n) {
            str[count] = 'A' + r -1;
        } else if (r && n) {
            str[count] = 'A' + r - 1;
            count++;
            if (n <= 26) {
                str[count] = 'A' + n -1;
                count++;
                n = n/26;
            }
        }
    }
    str[count] = '\0';

    //printf("str %s \n", str);
}

int
main (int argc, char *argv[])
{
    int i = 1, n;
    char str[32] = {0};

    if (argc <= 1) return 1;

    while (i < argc) {
        n = strtol(argv[i], 0, 0);
        print_col_str(str, n);
        printf(" n %d str %s\n", n, str);
        memset(str, '\0', 32);
        i++;
        getchar();
    }
}
