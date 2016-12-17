#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int debug = 1;
int dp[1001] = {0};
int qsize[10] = {0};
int tp[10] = {0};
    int
get_digit (int val)
{
    int count = 0l;

    while (val) {
        count++;
        val = val/10;//33 (1), 3 (2), 0 (3)
    }
    return count;
}

void
get_dp_sum (int val, int gd)
{
    int idx, i, count = 0, m;

    for (i = 1; i < 10; i++) {
        dp[i]= dp[i-1]+i;
    }
    dp[10] = dp[9];

    gd -= 2;
    idx = 10;
    m = 1;
    while (gd) {
        idx = idx*10; //100 (3), 1000 (4)
        count = 0;
        while (count <= 9) {
            dp[idx] +=  dp[idx/10]+10*m*count; 
            count++;
        }
        m = m*10;
        gd--;
    }
}

// 0, 1, 3, 6
int
get_sum (int val, int gd, int base)
{
    int sum = 0, count = 0, denom, m;
    if (gd == 1) {//return dp[val]; // 3, 4, 5, 6
        if (debug) {
            printf("base %d val %d dp %d %d\n", base, val, dp[base+val],
                    dp[val ? val-1 : 0]);
        }
        if (val) 
            return dp[base+val] - dp[val-1];
        else return base;
    }

    m = tp[gd];
    denom = val/qsize[gd];
    while (count < denom) {
        sum += dp[qsize[gd]]+ tp[gd]*count;
        count++;
    }

    if (debug) {
        printf(" qsize[%d] = %d val/qsize = %d dp[qsize] = %d tp %d\n", gd, qsize[gd], denom,
                sum, tp[gd]);
    }

    sum += get_sum(val%qsize[gd], gd-1, denom);
    
    return sum;
}

int
main (int argc, char *argv[])
{

   int gd, i, val = 3333, sum;

   val = strtol(argv[1], 0, 0);
   gd = get_digit(val);
   printf("val %d gd %d\n", val, gd);
   get_dp_sum(val, gd);

   if (debug) {
       for (i = 0; i <= 10; i++) {
            printf(" dp[%d] = %d ", i, dp[i]);
        }
   }
   qsize[1] = 1;
   tp[1] = 1;
   tp[2] = 10;
   for (i = 2; i <= 5; i++) {
       qsize[i] = qsize[i-1]*10; 
       tp[i] = tp[i-1]*10; 
   }
   if (debug) 
       printf(" dp[100] = %d  dp[1000]=%d\n",  dp[100], dp[1000]);
   sum = get_sum(val, gd, 0);
   printf("sum %d\n", sum);  
}
