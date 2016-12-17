#include <stdio.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

typedef struct rules_ {
    int u[32];
    int l_exp;
    int spidx[32];
    int fs;
} rules;

typedef enum fail_reasons {
    UPPER_CASE_FAIL = 0,
    LOWER_CASE_EXP_FAIL,
    NO_SPACE_FAIL,
    FS_FAIL,
    CONT_SPACE_FAIL,
    CONT_CAPS_FAIL,
    EOK,
} fr;

const char error[][32] = {
    {"UPPER_CASE_FAIL"},
    {"LOWER_CASE_EXP_FAIL"},
    {"NO_SPACE_FAIL"},
    {"FS_FAIL"},
    {"CONT_SPACE_FAIL"},
    {"CONT_CAPS_FAIL"},
    {"EOK"}
    };

fr
sent_rules_check (rules *r, char *str)
{
    int sidx = 0, idx = 0, count = 0, skip = 0;

    if ((*str >= 'A') && (*str <= 'Z')) {
        r->u[idx] = count;
        idx++;
        r->l_exp = TRUE;
    } else {
        return UPPER_CASE_FAIL;
    }
    str++;

    while (*str != '\0') {
        count++;
    
        if (r->fs) return FS_FAIL;

        if (*str == ' ') {
            r->spidx[sidx] = count;
            if (sidx) {
                if (r->spidx[sidx] == r->spidx[sidx]+1) {
                    return CONT_SPACE_FAIL;
                }
            }
            skip = TRUE;
            sidx++;
        }

        if ((*str >= 'A') && (*str <= 'Z')) {
            if (r->l_exp) return LOWER_CASE_EXP_FAIL;
            r->l_exp = TRUE;
            r->u[idx] = count;
            if (idx > 0) {
                if (r->u[idx-1] == r->u[idx]+1) {
                    return CONT_CAPS_FAIL;
                }
            }
            skip = TRUE;
            idx++;
        }
        
        if (*str == '.') r->fs++;
        if (r->l_exp && !skip) {
            r->l_exp = FALSE; 
        } else if (skip) {
            skip = FALSE;
        }

        str++;
    }   

    if (!sidx) return NO_SPACE_FAIL;
    if (!r->fs) return FS_FAIL;

    return EOK;
}

int
main (int argc, char *argv[])
{
    int i = 0;
    fr reason;
    rules r = {0};
    char str[][64] = { {"My name is Ram."},
        {"The vertex is S."},
        {"I am single."},
        {"I love Geeksquiz and Geeksforgeeks."},
        {"My name is KG."},
        {"I lovE cinema."},
        {"GeeksQuiz. is a quiz site."},
        {"  You are my friend."},
        {"I love cinema"} 
    };

    while (i < 9) {
        reason = sent_rules_check(&r, str[i]); 
        printf("sentense %s HAS %s \n", str[i], error[reason]);
        i++;
        memset(&r, 0, sizeof(rules));
        getchar();
    }
}
