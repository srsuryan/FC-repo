#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "qlib.h"
#include "treelib.h"

static node_td *root;

void
inorder (node_td *node)
{
    if (!node) return;

    inorder(node->left);
    printf(" <<%d>> %s ", node->i, node == root ? "ROOT" : "");
    inorder(node->right);
}

void
tree_create_bst (node_td *node, int i)
{

    node_td *trav, *prevl, *prevr;

    trav = root;

    while (trav) {
        if (i > trav->i) {
            prevr = trav;
            prevl = NULL;
            trav = trav->right;
        } else if ( i < trav->i) {
            prevr = NULL;
            prevl = trav;
            trav = trav->left;
        } else {
            printf("Value not added %d exists\n", i);
            return;
        }
    }

    if (prevl) {
        prevl->left = node;
    } else if (prevr) {
        prevr->right = node;
    }
}


node_td *
tree_create_bft (int argc, char *argv[])
{
	int *a;
	node_td *root, *parent, *node, *node1, *node2;
	int fd1, i, rv;
	qelem_td *qelem = NULL;
        queue_td *q = NULL;

        rv = lib_init(QUEUE, &q, &fd1);
        if (!rv || !q) {
            printf("Lib init failed %d %p\n", rv, q);
            return 1;
        }

        a = get_from_main(argc, argv);

        root = (node_td *)calloc(1, sizeof(node_td));
        root->i = (int)strtol(argv[1], 0, 0);

        node = root;
        qpush(fd1, node);
        i = 1;
        while (a && a[i] != 0xFFFF && (i < 32)) {
                parent = qpop(fd1);
                node1 = node2 = NULL;
                node1 = (node_td *)calloc(1, sizeof(node_td));
                node1->i = a[i];
                parent->left = node1;
                i++;
                if (a[i] != 0xFFFF && (i < 32)) {
                   node2 = (node_td *)calloc(1, sizeof(node_td));
                   node2->i = a[i];
                   parent->right = node2;
                   i++;
                } else break;
                qpush(fd1, node1);
                qpush(fd1, node2);
        }
	lib_done(fd1);
	return root;
}
