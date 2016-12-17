#include <stdio.h>

int
main (int argc, char *argv[])
{
    char *str, *ptr;
    int i = 1, count, sum;

    if (argc <= 1) return 1;

    while (i < argc) {
        printf("string %s, argc %d\n", argv[i], argc);
        str = argv[i];
        ptr = str;
        while (*str != '\0') str++;
        str--;
        count = 1;
        sum = 0;
        while (str >= ptr) {
               sum = sum + (*str - 'A' + 1)*count;
               str--; 
               count = count*26;
        }
        printf("%s is %d \n", argv[i], sum);
        getchar();
        i++;
    }
}
