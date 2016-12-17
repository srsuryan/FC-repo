

int
biotonic (int *arr, int max)
{

   int i, j, dp[32], dpr[32], g;

  
   for (j = 0; j < max; j++) {
	dp[j] = 1;
	dpr[j] = 1;
   }
   
   for (i = 1; i < max; i++) {
       for (j = 0; j < i; j++) {
	    if (a[i] > a[j]) {
		g = dp[j]+1;
                if (g > dp[i]) {
		    dp[i] = dp[j]+1;
		}
	    }
       }
    }

   for (i = max-2; i >= 0; i--) {
       for (j = max-1; j > i; j--) {
	    if (a[i] > a[j]) {
		g = dpr[j]+1;
                if (g > dpr[i]) {
		    dpr[i] = dpr[j]+1;
		}
	    }
       }
    }

}
   
