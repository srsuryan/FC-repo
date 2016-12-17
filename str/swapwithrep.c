#include <stdio.h>
#include <string.h>

void
printwithrep (char *str, int max, char *data, int idx)
{
    int i;

    if (idx == max) {
        data[max] = '\0';
        printf("str %s max %d\n", data, max);
        return;
    }

    for (i = 0; i < max; i++) {
        data[idx] = str[i];
        printwithrep(str, max, data, idx+1);
    }
}

int
main (int argc, char *argv[])
{
    char data[4] = {0};
    char str[4] = {"ABC"};

    printwithrep(str, strlen(str), data, 0);
}
