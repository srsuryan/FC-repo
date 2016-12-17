

int 
main (int argc, char *argv[])
{
    char *str;

    
    while ((str[i] != '\0') && (str[i] == '')) {
        i++;
    }

    if (str[i] == '\0') return;

    while (str[i] != '\0') {

        if ((str[i] == '') && (prev)) {
            if (prev->i == str[i]) {
            } else if ((prev->i == '') &&
                       (str[i] = '.')) {
                prev->i = '.';
            }
            i++;
            continue;
        } else {
            node = calloc();
            node->i = str[i];
            if (!prev) {
                prev = node;
                start = prev;
            } else {
                prev->next = node;
            }
        }
        i++;
    }
}
