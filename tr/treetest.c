#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../ll/util.h"
#include "../ll/ll.h"
#include "treelib.h"

    int
main (int argc, char *argv[])
{
    int *a;
    node_td *root;
    sll *start;

    a = get_from_main(argc, argv);
    root = cons_tree(a);
    print_tr(root, "main");
}
