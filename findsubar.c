

int
find_subarr_match (int *arr)
{
  int sum = a[0], i, j;

  j = 0;
  i = 1;
  
  while ((j < n) && (i < n)) {
      if (sum == match) {
	  if (i != j) {
	  	printf(" i %d j %d \n", i, j);
	  	return sum;
	  } else if (i == j) {
		if (a[i] == match) {
	  		printf(" i %d j %d \n", i, j);
	  		return sum;
		} else {
		    printf("\n not found\n");
		    return -1;
		}
          }
      } else if (sum < match) {
      	  sum = sum == -1 ? 0 : sum + a[i];
	  i++;
      } else {
          sum = sum - a[j];
	  j++;
      }
  }

  return -1;
}

