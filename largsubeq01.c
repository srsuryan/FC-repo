#include <stdio.h>
#include <math.h>
#include <stdlib.h>
/*

Largest subarray with equal number of 0s and 1s

Given an array containing only 0s and 1s, find the largest subarray which contain equal no of 0s and 1s. Expected time complexity is O(n).

Examples:

Input: arr[] = {1, 0, 1, 1, 1, 0, 0}
Output: 1 to 6 (Starting and Ending indexes of output subarray)

Input: arr[] = {1, 1, 1, 1}
Output: No such subarray

Input: arr[] = {0, 0, 1, 1, 0}
Output: 0 to 3 Or 1 to 4
*/

int get (int i)
{
  switch (i) {
  case 1:
	return 1;
  case 0:
	return -1;
  default:
	return 0xFF;
  }
}

int 
findfromleft (int *arr, int max, int sumupto, int *s, int *e)
{
   int sum = 0, i = 0;

   while (i < max) {
       sum += get(arr[i]);
       if (sumupto == sum) {
	   *s = i+1;
	   *e = max -1;
	   return abs(*s - *e +1) ;
       }
       i++; 
   }
   return 0xFF;
}

int 
findfromright (int *arr, int max, int sumupto, int *s, int *e) 
{
   int sum = 0, i = max-1;

   while (i >= 0) {
       sum += get(arr[i]);
       if (sumupto == sum) {
	  *s = 0;
	  *e = i-1;
	  return abs(*s - *e +1);
       }
       i--;
   }

   return 0xFF;
}

int 
findfrombothends (int *arr, int max, int sumupto, int *s, int *e) 
{
   int sum = 0, i = 0, j = max -1;

   while (i < j) {
       sum += get(arr[i]);
       if (sumupto == sum) {
	   *s = i+1; 
	   *e = j;
	   return abs(*s - *e +1);
       }	
       sum += get(arr[j]);
       if (sumupto == sum) {
           *s = i;
	   *e = j-1;
	   return abs(*s - *e +1);
       }
       i++;
   }

   return 0xFF;
}

/* Driver program to test above functions*/
int main()
{
    int diff1, s, e, sum = 0, i = 0, arr[] =  {1, 0, 0, 1, 0, 1, 1};
    int size = sizeof(arr)/sizeof(arr[0]);

    while (i < size) {
	sum += get(arr[i]);
        i++;
     }
     printf("sum %d \n", sum);
     getchar();
    if (sum) {
        diff1 = findfromleft(arr, size, sum, &s, &e); 
    	printf("Difs %d  s %d e %d\n", diff1, s, e);
        diff1 = findfromright(arr, size, sum, &s, &e);
    	printf("Difs %d  s %d e %d\n", diff1, s, e);
        diff1 = findfrombothends(arr, size, sum, &s, &e);
    	printf("Difs %d  s %d e %d\n", diff1, s, e);
    }
    return 0;
}
