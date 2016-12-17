#include <stdio.h>
/*

Stock Buy Sell to Maximize Profit

The cost of a stock on each day is given in an array, find the max profit that you can make by buying and selling in those days. For example, if the given array is {100, 180, 260, 310, 40, 535, 695}, the maximum profit can earned by buying on day 0, selling on day 3. Again buy on day 4 and sell on day 6. If the given array of prices is sorted in decreasing order, then profit cannot be earned at all.


50  100   90 80 95     180 260 240     81 310 40    30 10 60 101 138 535 695

50 - 100
50 - 240
50 - 340
{100, 180, 260, 310, 40, 535, 695};
{50, 100, 90, 80, 95, 180, 260, 240, 81, 310, 40, 30, 10, 60, 101, 138, 535, 695};
*/

//int tdiff[32] = {0};

int
brokarage (int *a, int max) 
{
	int low, high, i, ndiff, tdiff, lowidx;
	
	low = a[0];
	high = a[1];
	i = 2;
	tdiff = -1;
	lowidx = 0;
	while (i < max) {
		if (low < high) {
			if (high < a[i]) {
			    high = a[i];
			    i++;
			    //continue;
			} else {
			    ndiff = high - low;
			    if (ndiff > tdiff) {
				tdiff = ndiff;
				printf("(%d, %d) a[%d] = %d a[%d] = %d [%d]\n", low, high, lowidx, low, i, a[i], tdiff);
			        getchar(); 
			     }
			     if (a[i] > low) {
				    high = a[i]; //FIXME:
				    i++;
				    if (i >= max) return tdiff;
				    //continue;
			     } else {
				   low = a[i];
				   lowidx = i;
				   i++;
				   if (i >= max) return tdiff;	
				   high = a[i+1]; //FIXME CHECK
				   i++;
				   if (i >= max) return tdiff;
				   //continue;
			     }
			}
		} else {
			low = high;
			high = a[i];
			i++;
			printf("3.(%d, %d) a[%d] = %d a[%d] = %d [%d]\n", low, high, lowidx, low, i, a[i], tdiff);
			getchar(); 
			if (i >= max) return tdiff;
		}
	}
	
        ndiff = high - low;
        if (ndiff > tdiff) {
            tdiff = ndiff;
            printf("4.(%d, %d) a[%d] = %d a[%d] = %d [%d]\n", low, high, lowidx, low, i, a[i], tdiff);
            getchar();
        }  
	return tdiff;
}


// Driver program to test above functions
int main()
{
    // stock prices on consecutive days
    //int price[] = {100, 180, 260, 310, 40, 535, 695};
    int price[] = {50, 100, 90, 80, 95, 180, 260, 240, 81, 310, 40, 30, 10, 60, 101, 695};
    int n = sizeof(price)/sizeof(price[0]), val;
 
    // fucntion call
    val = brokarage(price, n);
 
    printf("Val %d \n", val);
    return 0;
}
