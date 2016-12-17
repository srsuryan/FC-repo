#include <stdio.h>
#include <stdlib.h>

int debug = 1;
int 
maxof3 (int a, int b, int c)
{
    int max;
 
    if (a > b) max = a;
    else max = b;

    if (max > c) return max;
    return c;
}

int 
ospgame (int a[], int i, int l, int sum, int count, int max)
{

     if (count*2 > max) return sum;

     if (debug) {
         printf(" i %d l %d sum %d count %d\n", i, l, sum, count);
         getchar();
     }

     return  maxof3(ospgame(a, i+1, l, sum+a[i], count+1, max), 
                    ospgame(a, i, l-1, sum+a[l], count+1, max),
                    ospgame(a, i+2, l, sum+a[i+1], count+1, max));
}

int main()
{
    int arr1[] = {8, 15, 3, 7};
    int n = sizeof(arr1)/sizeof(arr1[0]);
    printf("%d\n", ospgame(arr1, 0, n-1, 0, 0, n));
 
    int arr2[] = {2, 2, 2, 2};
    n = sizeof(arr2)/sizeof(arr2[0]);
    //printf("%d\n", ospgame(arr2, n));
 
    int arr3[] = {20, 30, 2, 2, 2, 10};
    n = sizeof(arr3)/sizeof(arr3[0]);
    //printf("%d\n", ospgame(arr3, n));
 
    return 0;
}
