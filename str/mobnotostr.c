#include <stdio.h>
#include <string.h>
 
const char hashTable[10][5] = {"", "", "abc", "def", "ghi", "jkl",
                               "mno", "pqrs", "tuv", "wxyz"};
 

void
printWords (int num[], int nidx, int max, char *str, int idx)
{
    int i;

    if (nidx >= max) {
        str[4] = '\0';
        printf("Nidx %d max %d, str %s idx %d\n", nidx, max, str, idx);
        return;
    }

    for (i = 0; i < strlen(hashTable[num[nidx]]); i++) {
        str[idx] = hashTable[num[nidx]][i];
        printWords(num, nidx+1, max, str, idx+1);
    }

}
 
//Driver program
int main(void)
{
    char str[5] = {0};
    int number[] = {2, 3, 4};
    int n = sizeof(number)/sizeof(number[0]);

    printf("HashTable %ld %ld %ld\n", strlen(hashTable[2]), strlen(hashTable[3]), strlen(hashTable[7]));
    getchar();
    printWords(number, 0, n, str, 0);
    return 0;
}
