#include <string.h>
#include <stdio.h>

void
interleave (char *str1, char *str2, int n1, int n2, char *strilv, int i)
{

    if (!n1 && !n2) {
        strilv[4] = '\0';
        printf("%s\n", strilv);
    }

    if (n1 != 0) {
        strilv[i] = str1[0];
        printf("1 %s\n", strilv);
        getchar();
        interleave(str1+1, str2, n1-1, n2, strilv, i+1);
    }


    if (n2 != 0) {
        strilv[i] = str2[0];
        printf("2 %s\n", strilv);
        getchar();
        interleave(str1, str2+1, n1, n2-1, strilv, i+1);
    }
 
}

int 
main (int argc, char *argv[])
{
    char strilv[32] = {0}, *str1 = argv[1], *str2 = argv[2];

    if (argc <3) return 1;

    printf("s1 %s %ld S2 %s %ld\n", argv[1], strlen(argv[1]), argv[2], strlen(argv[2]));
    getchar();
    interleave(str1, str2, strlen(str1), strlen(str2), strilv, 0);
}

