#include<stdio.h>
#include<string.h>


int debug = 1;

int 
max (int i, int j)
{
    if (i > j) return i;
    return j;
}
 
int findLength (char *str, int n)
{
    int ans = 0; // Initialize result
 
    // Consider all possible midpoints one by one
    for (int i = 0; i <= n-2; i++)
    {
        /* For current midpoint 'i', keep expanding substring on
           both sides, if sum of both sides becomes equal update
           ans */
        int l = i, r = i + 1;
 
        /* initialize left and right sum */
        int lsum = 0, rsum = 0;

        printf("--------OL---------- \n");
        /* move on both sides till indexes go out of bounds */
        while (r < n && l >= 0)
        {
            lsum += str[l] - '0';
            rsum += str[r] - '0';
            if (debug) {
                printf("(%c %c) l %d r %d lsum %d rsum %d\n", 
                        str[l], str[r], l, r, lsum, rsum);
                getchar();
            }

            if (lsum == rsum)
                ans = max(ans, r-l+1);
            l--;
            r++;
        }
    }
    return ans;
}
 
// Driver program to test above function
int main()
{
    const char *str = "0538123";
    printf("Length of the substring is %d\n", findLength(str, strlen(str)));
    return 0;
}
