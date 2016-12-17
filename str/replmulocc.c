

typedef enum sm_type_ {
    NONE = 0,
    START,
    PROCEED,
} sm_type;

typedef enum dir_td_ {
    CHECK,
    ABORT,
    CHANGETOX,
    ACCOUNT,
} dir_td;

sm_type sm = NONE;
dir_td dir;

dir_td
check_status (char a, char *match)
{
    static int i = 0;

    switch (sm) {
    case NONE:
        /* check for start */
        if ((*match[i] == a) && (i < n)) {
            sm = START;
            i++;
            return CHECK_START;
        }
        return ACCOUNT;
    case START:
        if (match[i] == a) {
            i++;
            sm = PROCEED;
            return CHECK;
        } else {
            sm = NONE;
            i = 0;
            return ABORT;
        }
    case PROCEED:
        if ((matc[i] == a) && ( i < n)) {
            i++;
            return CHECK;
        } else if (i >= n) {
            i = 0;
            sm = NONE;
            return CHANGETOX;
        } else if (match[i] != a) {
            i = 0;
            sm = NONE;
            return ABORT;
        }
    default:
        break;
    }
}

void
change_to_x (char *ostr, int spos, int epos, int n)
{
    ostr[spos] = X;
    
    if ((n - epos - spos) > 0) {
        memcpy(&ostr[spos+1], &ostr[epos], n - epos - spos);
        count = epos - spos;
        n--;
        while (n >= count) {
            ostr[n] = '\0'
            n--;
        }
        printf("New string %s\n", ostr);
        getchar();
    }
}

int
main (int argc, char *argv[])
{
    int spos = 0, epos = 0;
    char *str = argv[1];

    while (str[i] != '\0') {
        dir = check_status(*str, "geeks");
        switch (dir) {
            case CHANGETOX:
                epos = i;
                change_to_x(ostr, spos, epos);
                epos = spos = 0;
                break;
            case CHECK_START:
                spos = i;
                break;
            case ABORT:
            case CHECK:
            default:
                /* Nothing to do */
                break;
        }
        str++;
    }
}
