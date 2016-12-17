


bool
probe (int i, int j)
{


     si = i;
     sj = j;

     /* DOWN */
     for (i = si; i < ROW, sj < COL; i++) {
	  if (mat[i][j] == pat[count]) {
	      count++;
	  } else {
	      break;
	  }
	
	  if (count = strlen(pat)) {
	      return VERTICLE;
	  }
      }

      /* UP */
      for (i = si; i >= 0, sj > 0; i--) {
	  if (mat[i][j] == pat[count]) {
	      count++;
	  } else {
	      break;
	  }
	  if (count = strlen(pat)) {
	      return VERTICLE;
	  }
      }

      /* RIGHT */
      for (j = sj; j < COL; j++) {
	  if (mat[i][j] == pat[count]) {
	      count++;
	  } else {
	      break;
	  }
	  if (count = strlen(pat)) {
	      return HORIZONTAL;
	  }
      }

      /* LEFT */
      for (j = sj; j >= 0; j--) {
	  if (mat[i][j] == pat[count]) {
	      count++;
	  } else {
	      break;
	  }
	  if (count = strlen(pat)) {
	      return HORIZONTAL;
	  }
      }
      result NONE;
}
	
