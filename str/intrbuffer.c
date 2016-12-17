#include <stdio.h>
#include <string.h>

int debug = 1;
void
insert_buf (char *str, char *nstr, int pos)
{
    int i = 0;

    while (i <= pos) {
        nstr[i] = str[i];
        i++;
    }
    nstr[i] = ' ';
    while (i < strlen(str)) {
        nstr[i+1] = str[i];
        i++;
    }
}

void
insert_nstr (char *str, int pos, int gap) 
{
    char nstr[32];
    int i;

    if ((pos+gap) > strlen(str)) {
        if (debug) {
            printf("pos %d gap %d is larger than str %s %d\n", pos, gap, str, strlen(str));
            //getchar();
        }
    }
    memset(nstr, '\0', 32);
    for (i = pos+gap; i < strlen(str); i++) {
        insert_buf(str, nstr, i);
         if (debug) {
             printf("%d.ostr %s nstr %s \n", gap, str, nstr);
             //getchar();
         }
        insert_nstr(nstr, i, gap);
    }
}
int
main (int argc, char *argv[])
{
    int i, n;
    char *str = argv[1], nstr[32];

    if (argc <= 1) return 0;

    memset(nstr, '\0', 32);

    for (i = 0; i < strlen(str); i++) {
         insert_buf(str, nstr, i);
         if (debug) {
             printf("nstr %s \n", nstr);
             //getchar();
         }
         insert_nstr(nstr, i, 2);
         memset(nstr, '\0', 32);
    }
}
