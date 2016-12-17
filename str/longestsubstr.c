#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int debug = 1;

typedef struct max_ {  
        int m;
        int spos;
        int epos;
} max;

typedef struct strcap_ {
      int alpha[26];
      char ns[32];
      int nlen;
      int ntuc;
      int spos;
      int k;
      max mx;
} substr_td;

char *
print_substr (char *str, int spos, int epos, char *pstr) 
{
    int count = 0;

        if (spos > epos) {
            printf("Invalid find %d %d\n", spos, epos);
            return "invalid";
        }
        
        while (spos <= epos) {
            pstr[count] = str[spos];
            spos++;
            count++;
        }
        return pstr;
}

int
get_new_spos (int cpos, int nidx, char *str) 
{
   int oidx = nidx;
   char *ns, *ptr = &str[nidx], pstr[32] = {0};
   
   while (nidx && (str[nidx] != str[cpos])) {
        nidx--;
   }
   if (debug) {
       printf("New spos %d, nidx %d newstr %s\n", nidx+1, oidx, print_substr(str, nidx+1, oidx, pstr));
   }
   return nidx +1;
}

int
fill_new_pos (char *str, int e, substr_td *substrh)
{
        int i, count = 0, ec;

        memset(substrh->alpha, 0, 32*sizeof(int));
        i = substrh->spos;
        substrh->nlen = substrh->ntuc = 0;
        while (i <= e) {
            ec = str[i]-'a';
            if (!substrh->alpha[ec]) {
                substrh->ntuc++;
            }
            substrh->alpha[ec]++;
            substrh->ns[count] = str[i];
            i++;
            count++;
            substrh->nlen++;
        }
    return count;
}

void
calc_substr (char *str, int n, int k)
{
    int idx = 0, count = 0, sc = 0;
    char *ostr = str, pstr[32] = {0};

    substr_td substrh = {0};

     substrh.k = k;

     while (*str != '\0') {
         count = *str - 'a';
         if (substrh.alpha[count]) { 
             substrh.ns[sc] = *str;
             sc++;
             substrh.alpha[count]++;
             substrh.nlen++;
             idx++;
             str++;
         } else {
             if (substrh.ntuc +1 <= k) {
                /* New char, have space */
                 substrh.ns[sc] = *str;
                 sc++;
                 substrh.alpha[count]++;
                 substrh.nlen++;
                 substrh.ntuc++;
                 idx++;
                 if (debug) {
                     printf("ns %s\n", substrh.ns);
                     getchar();
                 }
             } else {
                 /* move if the max is reached */
                 if (substrh.nlen > substrh.mx.m) {
                     substrh.mx.m = substrh.nlen;
                     substrh.mx.spos = substrh.spos;
                     substrh.mx.epos = idx - 1;
                 }
                 sc = 0;
                 memset(substrh.ns, '\0', 32);
                 substrh.spos = get_new_spos(substrh.spos, idx, ostr);
                 sc = fill_new_pos(ostr, idx, &substrh);
                 idx++;
                 if (debug) {
                     printf("max is %d spos %d epos %d\n", substrh.mx.m, substrh.mx.spos, substrh.mx.epos); 
                     printf("New spos %d epos %d ntuc %d nlen %d %s\n", substrh.spos, idx, substrh.ntuc, substrh.nlen, 
                             print_substr(ostr, substrh.spos, idx, pstr));
                     getchar();  
                 }       
             }
             str++;   
         }
     }

     memset(pstr, '\0', 32);
     printf("New string %s max %d %d %d %s\n", substrh.ns, substrh.mx.m, substrh.mx.spos, substrh.mx.epos,
             print_substr(ostr, substrh.mx.spos, substrh.mx.epos, pstr));
}

int
main (int argc, char *argv[])
{
    int n;
    char *str = argv[1];

    if (argc <= 1) return -1;
    printf("%s\n", str);
    calc_substr(str, strlen(str), 3);
}



