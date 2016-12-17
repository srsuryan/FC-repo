
typedef ana_ {
    char alpha[26];
    int total;
} anagram;

anagram ana[32] = {0};
anagram real[32];

void
set_ana (char *word, int rc) 
{
    while (*word != '\0') {
        real[rc].alpha[*word]++;
        word++;
    }
}

int
check_new_word (char *word, int rc)
{
    int i = 0, set = 0;

    while (i < rc) {
        while (*word != '\0') {
            if (real[rc].alpha[*word]) {
                real[rc].alpha[*word]--;
                real[rc].total--;
            } else {
                memset(&real[rc], 0, sizeof(anagram));
                set_ana(word, rc);
                i++;
                set = FALSE;
                break;
            }
            word++;
        }
        i++;
    }       
    
    if (!set) return FALSE; 
}

// Driver program to test above functions
int main()
{
    int rc_max = 0;
    char* wordArr[] = {"cat", "dog", "tac", "god", "act", "gdo"};
    int size = sizeof(wordArr) / sizeof(wordArr[0]);
    
    set_ana(wordArr[0], rc_max);
    rc_max++;
    count = 1;
    while (count < size) {
        if (!check_new_word(wordArr[count], rc_max)) {
            set_ana(wordArr[count], rc_max); 
            rc_max++;
        }     
    }

    printAnagramsTogether(wordArr, size);
    return 0;
}
