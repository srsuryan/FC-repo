#include <stdio.h>
#include <string.h>


void
revstr (char *str, int i)
{

    if (i < 0) return;

    printf("%c",str[i]);
    revstr(str, i-1);
}

int 
main (int argc, char *argv[])
{
    char *str;
    int i, j, n, c;

    if (argc <= 1) return 1;

    revstr(argv[1], strlen(argv[1]));
    printf("\n");
}
