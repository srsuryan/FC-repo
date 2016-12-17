#include <stdio.h>

#define N 0
#define E 1
#define S 2
#define W 3

static int dir = E;
int debug = 1;
void
set_newps (int lr)
{
    int oldd = dir;

    dir = (4 + dir + lr)%4;
    if (debug) {
        printf("old pos %d new pos %d\n", oldd, dir);
    }
}

void
move_up_oneps (int *x, int *y)
{

    switch (dir) {
    case N:
        (*y) = (*y) + 1;
        break;
    case E:
        (*x) = (*x) + 1;
        break;
    case S:
        (*y) = (*y) - 1;
        break;
    case W:
        (*x) = (*x) - 1;
        break;
    default:
        break;
    }
    if (debug) {
        printf("New pos %d %d\n", *x, *y);
        getchar();
    }
}

int
main (int argc, char *argv[])
{
    int x = 0, y = 0;
    char *str = argv[1];

    if (argc <=1) return -1;

    while (*str != '\0') {
        switch (*str) {
        case 'G':
            move_up_oneps(&x, &y);
            break;
        case 'L':
        case 'R':
            set_newps((*str == 'L') ? -1 : 1); 
        default:
            break;
        }
        str++;
    }

    printf("x %d y %d\n", x, y);
}
