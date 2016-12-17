/*
 * Given an an unsorted array, sort the given array. 
 * You are allowed to do only following operation on array.
 * flip(arr, i): Reverse array from 0 to i 
 * 
 * {23, 10, 20, 11, 12, 6, 7};
 */

int
pcksort (int *arr, int val, int n, int max)
{
	int i = 0;

	arr[n] = val;
	if (arr[n-1] < arr[n]) return;

	rev(arr, n-1);
	rev(arr, n);

	i = 1;
        {
		while ((arr[0] > arr[i]) && (i < max)) {
			i++;
		}
   
                if (i == max) return;

		rev(arr, i-1);
		i = 1;
	} while (i >= 0);
}
