#include <stdio.h>

void
test (char *s1, char *s2)
{
    char *os1 = s1, *os2 = s2;

    while ((*s1 != '\0') &&
            (*s2 != '\0')) {
        if (*s1 == *s2) {
            s1++;
            s2++;
            continue;
        }
       
        if (*s1 == '?') {
            s1++;
            s2++;
            continue;
        } 
        if (*s1 == '*') {
            s1++;
            if (*s1 == '*' || *s1 == '?') return;
            while (*s1 != *s2) {
                if (*s2 == '\0') {
                    if (*(s1) == '\0') {
                        printf("3. yes %s %s matches\n", os1, os2);
                        return;
                    }
                    printf("1. No %s %s do not match\n", os1, os2);
                    return;
                }
                s2++;
            }
        }
    }

    if ((*s1 == *s2) && (*s1 == '\0')) {
        printf("2. Yes %s %s matches\n", os1, os2);
    } else {
        printf("4. No %s %s do not matche\n", os1, os2);
    }
}

int main()
{
    test("g*ks", "geeks"); // Yes
    getchar();
    test("ge?ks*", "geeksforgeeks"); // Yes
    getchar();
    test("g*k", "gee");  // No because 'k' is not in second
    getchar();
    test("*pqrs", "pqrst"); // No because 't' is not in first
    getchar();
    test("abc*bcd", "abcdhghgbcd"); // Yes
    getchar();
    test("abc*c?d", "abcd"); // No because second must have 2
                             // instances of 'c'
    getchar();
    test("*c*d", "abcd"); // Yes
    getchar();
    return 0;
}
