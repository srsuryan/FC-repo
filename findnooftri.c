#include <stdio.h>

/*
 
Count the number of possible triangles

Given an unsorted array of positive integers. Find the number of triangles that can be formed with three different array elements as three sides of triangles. For a triangle to be possible from 3 values, the sum of any two values (or sides) must be greater than the third value (or third side).
For example, if the input array is {4, 6, 3, 7}, the output should be 3. There are three triangles possible {3, 4, 6}, {4, 6, 7} and {3, 6, 7}. Note that {3, 4, 7} is not a possible triangle.
As another example, consider the array {10, 21, 22, 100, 101, 200, 300}. There can be 6 possible triangles: {10, 21, 22}, {21, 100, 101}, {22, 100, 101}, {10, 100, 101}, {100, 101, 200} and {101, 200, 300}
         2                       8
{10, 21, 22, 23, 24, 26, 28, 29, 30,   100, 101, 200, 300}
*/


int 
howmt (int *arr, int i, int max)
{
	int sc = 0, j, k, savej, sum, count = 0;

	j = i +1;
	//do {
		savej = j;
		sum = arr[i]+arr[j];

		while (savej < max) {
			for (k = j+1; k < max; k++) {
				if (sum < arr[k]) {
					printf(" sum %d k arr[%d] =%d j %d savej %d \n", 
							sum, k, arr[k], j, savej);
					getchar();
					break;
				}
				//count++;
			}
			if ((k - savej -1) > 0) {
			    sc += k - savej -1;
		 	    printf(" sc %d sc2 (%d) k %d savej %d \n", sc, (k - savej -1), k, savej);
			    getchar();
			}
			savej++; // 22, 3rd idx
			sum = arr[i] + arr[savej];
			j = k - 1;
			//count = 0;
			//}
		}
	//} while (j < );
	return sc;
}   
   
// Driver program to test above functionarr[j+1]
int main()
{
    int i;//, arr[] =   {10, 21, 22, 23, 100, 101, 200, 300};
    int arr[] =  {10, 21, 22, 100, 101, 200, 300};
    int size = sizeof( arr ) / sizeof( arr[0] );
 
    for (i = 0; i < size; i++) {
    	printf("Total number of triangles possible is %d ",
           howmt(arr, i, size));
	getchar();
    }
 
    return 0;
} 
