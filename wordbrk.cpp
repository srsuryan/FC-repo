#include <iostream>
#include <string.h>
using namespace std;
 
bool wb[32] = {0};
/* A utility function to check whether a word is present in dictionary or not.
  An array of strings is used for dictionary.  Using array of strings for
  dictionary is definitely not a good idea. We have used for simplicity of
  the program*/
int dictionaryContains(string word)
{
    string dictionary[] = {"i", "ikea", "mobile","samsung","sam","sung","man","mango",
                           "icecream","and","go","like","ice","cream", "esamsun"};
    int size = sizeof(dictionary)/sizeof(dictionary[0]);
    for (int i = 0; i < size; i++)
        if (dictionary[i].compare(word) == 0)
           return true;
    return false;
}
 
// Returns true if string can be segmented into space separated
// words, otherwise returns false
bool wordBreak(string str)
{
    int size = str.size();
    if (size == 0)   return true;
 
    // Create the DP table to store results of subroblems. The value wb[i]
    // will be true if str[0..i-1] can be segmented into dictionary words,
    // otherwise false.
    memset(wb, 0, sizeof(wb)); // Initialize all values as false.
 
    for (int i=1; i<=size; i++)
    {
        // if wb[i] is false, then check if current prefix can make it true.
        // Current prefix is "str.substr(0, i)"
        string word = str.substr(0, i);
            printf(" %d %s \n", i, word.c_str());
        if (wb[i] == false && dictionaryContains(str.substr(0, i)))  {
            wb[i] = true;
        }
 
        // wb[i] is true, then check for all substrings starting from
        // (i+1)th character and store their results.
        if (wb[i] == true)
        {
            // If we reached the last prefix
            if (i == size)
                return true;
 
            for (int j = i+1; j <= size; j++)
            {
                // Update wb[j] if it is false and can be updated
                // Note the parameter passed to dictionaryContains() is
                // substring starting from index 'i' and length 'j-i'
                word = str.substr(i, j-i);
                if (wb[j] == false && dictionaryContains( str.substr(i, j-i) )) {
                    wb[j] = true;
                }
                printf("New word %s %d %d %d\n", word.c_str(), i, j-i, wb[j]);
 
                // If we reached the last character
                if (j == size && wb[j] == true)
                    return true;
            }
        }
    }
 
        
    // If we have tried all prefixes and none of them worked
    return false;
}
 
// Driver program to test above functions
int main()
{
    int i;
    //const string str = "ilikesamsungkkkk";
    const string str = "ilikeesamsun";

    wordBreak(str)? cout <<"Yes\n": cout << "No\n";
    for (int i = 0; i <= str.size(); i++) {
         printf("<<<wb[%d] = %d>>>> \n", i, wb[i]);
    }
#if 0
    wordBreak("iiiiiiii")? cout <<"Yes\n": cout << "No\n";
    wordBreak("")? cout <<"Yes\n": cout << "No\n";
    wordBreak("ilikelikeimangoiii")? cout <<"Yes\n": cout << "No\n";
    wordBreak("samsungandmango")? cout <<"Yes\n": cout << "No\n";
    wordBreak("samsungandmangok")? cout <<"Yes\n": cout << "No\n";
#endif
    return 0;
}
