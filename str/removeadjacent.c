#include <stdio.h>
#include <string.h>

int
main (int argc, char *argv[])
{
    int top, count;
    char a[32], *str;
    if (argc <= 1) return 1;

    memset(a, '\0', sizeof(a));
    printf("A+ str %s\n", a);
    str = argv[1];
    a[0] = str[0];
    count = top = 1;
    printf("A+ str %s\n", a);

    while (str[count] != '\0') {
        a[top] = str[count];
        count++;
        if (top && a[top] == a[top-1]) {
            top--;
            while (a[top] == str[count]) count++;
            printf("same char %c top %d new one %c %s\n", a[top], top, str[count], a);
            getchar();
        } else {
            printf("all fine %s\n", a);
            top++;
        }
    }
    a[top] = '\0';
    printf("Final String %s\n", a);
}

