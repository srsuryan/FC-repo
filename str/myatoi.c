#include <stdio.h>


int debug = 0;
int
power (int m)
{
    static int a[32] = {0};

    if (!m) {
        a[m] = 1;
        return 1;
    } 
    
    a[m] = a[m-1]*10;
    return a[m];
}

int
myAtoi (const char *str, char *last, int m)
{

    if (last == str) return 0;

    str--;

    if (debug) {
        printf("power[%d] = %d str %d last %p str %p\n", m, power(m), (*str - '0'), last, str);
        getchar();
    }
    return (power(m)*(*str - '0') + myAtoi(str, last, ++m));
}



// Driver program to test above function
int main(int argc, char *argv[])
{
    const char *str = argv[1];
    char *last = str;

    if (argc <= 1) return 1;

    while (*str != '\0') str++;
    
    int val = myAtoi(str, last, 0);
    printf ("%d\n", val);
    return 0;
}
